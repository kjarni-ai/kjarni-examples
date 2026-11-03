#include "kjarni.hpp"

#include <algorithm>
#include <print>
#include <ranges>
#include <string_view>
#include <vector>

int main() {
    auto embedder = kjarni::Embedder::create({.model = "minilm-l6-v2"});
    if (!embedder) {
        std::println(stderr, "could not load model: {}", embedder.error().message());
        return 1;
    }

    constexpr std::array docs = {
        std::string_view{"How do I reset my password?"},
        std::string_view{"What is your refund policy?"},
        std::string_view{"Do you ship internationally?"},
        std::string_view{"How do I update my billing address?"},
        std::string_view{"Where can I track my order?"},
    };

    std::vector<std::vector<float>> corpus;
    corpus.reserve(docs.size());
    for (std::string_view d : docs) {
        auto v = embedder->encode(d);
        if (!v) {
            std::println(stderr, "encode failed: {}", v.error().message());
            return 1;
        }
        corpus.push_back(v->to_vector());
    }

    constexpr std::string_view query = "I need to change my login credentials";
    auto q = embedder->encode(query);
    if (!q) {
        std::println(stderr, "encode failed: {}", q.error().message());
        return 1;
    }

    std::vector<std::pair<float, std::string_view>> scored;
    for (auto [i, doc] : std::views::enumerate(docs))
        scored.emplace_back(kjarni::cosine(q->values(), corpus[i]), doc);

    std::ranges::sort(scored, std::ranges::greater{},
                      &std::pair<float, std::string_view>::first);

    std::println("query: \"{}\"", query);
    for (auto [score, doc] : scored)
        std::println("  {:.4f}  {}", score, doc);
}
