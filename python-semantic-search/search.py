import sys

from kjarni import Embedder

docs = [
    "How do I reset my password?",
    "What is your refund policy?",
    "Do you ship internationally?",
    "How do I update my billing address?",
    "Where can I track my order?",
]

query = " ".join(sys.argv[1:]) or "I need to change my login credentials"

embedder = Embedder("minilm-l6-v2")
scored = sorted(((embedder.similarity(query, d), d) for d in docs), reverse=True)

print(f'query: "{query}"')
for score, doc in scored:
    print(f"  {score:7.4f}  {doc}")
