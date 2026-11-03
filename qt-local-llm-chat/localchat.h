#pragma once

#include <QFuture>
#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>

#include <atomic>
#include <memory>

struct ChatSession;

class LocalChat : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool ready READ ready NOTIFY stateChanged)
    Q_PROPERTY(bool generating READ generating NOTIFY stateChanged)
    Q_PROPERTY(QString status READ status NOTIFY stateChanged)
    Q_PROPERTY(QString transcript READ transcript NOTIFY transcriptChanged)

public:
    explicit LocalChat(QObject* parent = nullptr);
    ~LocalChat() override;

    bool ready() const { return m_session != nullptr; }
    bool generating() const { return m_generating; }
    QString status() const { return m_status; }
    QString transcript() const { return m_transcript; }

    Q_INVOKABLE void send(const QString& message);
    Q_INVOKABLE void stop() { m_stop = true; }
    Q_INVOKABLE void clear();

signals:
    void stateChanged();
    void transcriptChanged();
    void tokenProduced(const QString& token);

private:
    void setStatus(const QString& status);

    std::shared_ptr<ChatSession> m_session;
    QFuture<void> m_work;
    std::atomic<bool> m_stop = false;
    bool m_generating = false;
    QString m_status = "Loading the model...";
    QString m_transcript;
};
