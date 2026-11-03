#include "localchat.h"

#include <QtConcurrent>

#include "kjarni.h"

// A loaded model and the conversation that remembers its turns.
struct ChatSession {
    KjarniChat* chat = nullptr;
    KjarniChatConversation* conversation = nullptr;

    ~ChatSession() {
        kjarni_chat_conversation_free(conversation);
        kjarni_chat_free(chat);
    }
};

namespace {

QString lastError() {
    return QString::fromUtf8(kjarni_last_error_message());
}

std::shared_ptr<ChatSession> load(QString* error) {
    KjarniChatConfig config = kjarni_chat_config_default();
    config.model_name = "llama3.2-1b-instruct";
    config.system_prompt =
        "You are a concise assistant inside a desktop application. Answer in a few sentences.";
    config.quantized = 1;
    config.quiet = 1;

    auto session = std::make_shared<ChatSession>();
    if (kjarni_chat_new(&config, &session->chat) != KJARNI_ERROR_CODE_OK ||
        kjarni_chat_conversation_new(session->chat, &session->conversation) != KJARNI_ERROR_CODE_OK) {
        *error = lastError();
        return nullptr;
    }
    return session;
}

struct StreamContext {
    LocalChat* owner;
    const std::atomic<bool>* stop;
};

}  // namespace

LocalChat::LocalChat(QObject* parent) : QObject(parent) {
    // Emitted on the worker, delivered on this object's thread: a signal crossing
    // threads is queued, so the transcript is only ever touched on the GUI thread.
    connect(this, &LocalChat::tokenProduced, this, [this](const QString& token) {
        m_transcript += token;
        emit transcriptChanged();
    });

    m_work = QtConcurrent::run([] {
        QString error;
        auto session = load(&error);
        return std::make_pair(std::move(session), error);
    }).then(this, [this](std::pair<std::shared_ptr<ChatSession>, QString> loaded) {
        if (!loaded.first) {
            setStatus("Could not load the model: " + loaded.second);
            return;
        }
        m_session = std::move(loaded.first);
        setStatus("Ready. Nothing leaves this machine.");
    });
}

// The worker holds `this` to emit tokens, so it has to finish before the object goes.
LocalChat::~LocalChat() {
    m_stop = true;
    m_work.waitForFinished();
}

void LocalChat::send(const QString& message) {
    if (!ready() || m_generating || message.trimmed().isEmpty()) {
        return;
    }
    m_generating = true;
    m_stop = false;
    m_transcript += "You: " + message + "\n\nAssistant: ";
    emit transcriptChanged();
    setStatus("Generating...");

    m_work = QtConcurrent::run([this, session = m_session, text = message.toStdString()] {
        StreamContext context{this, &m_stop};
        // Returning false from the callback ends generation.
        const auto callback = [](const char* token, void* userData) -> bool {
            auto* ctx = static_cast<StreamContext*>(userData);
            emit ctx->owner->tokenProduced(QString::fromUtf8(token));
            return !ctx->stop->load();
        };
        const KjarniErrorCode code = kjarni_chat_conversation_stream(
            session->conversation, text.c_str(), nullptr, callback, &context, nullptr);
        return code == KJARNI_ERROR_CODE_OK ? QString{} : lastError();
    }).then(this, [this](const QString& error) {
        m_generating = false;
        m_transcript += "\n\n";
        emit transcriptChanged();
        setStatus(error.isEmpty() ? "Ready." : "Generation failed: " + error);
    });
}

void LocalChat::clear() {
    if (!ready() || m_generating) {
        return;
    }
    kjarni_chat_conversation_clear(m_session->conversation, /*keep_system=*/1);
    m_transcript.clear();
    emit transcriptChanged();
}

void LocalChat::setStatus(const QString& status) {
    m_status = status;
    emit stateChanged();
}
