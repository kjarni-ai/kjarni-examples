# Semantic search in Python without PyTorch

Rank text by meaning in Python with `pip install kjarni` and nothing else: no PyTorch, no
sentence-transformers, no ONNX Runtime, no numpy. The wheel is about 10 MB and holds the
native engine.

```bash
cd python-semantic-search
pip install kjarni
python search.py
python search.py where is my package
```

```
query: "I need to change my login credentials"
   0.5981  How do I reset my password?
   0.4067  How do I update my billing address?
   0.0767  Where can I track my order?
  -0.0027  What is your refund policy?
  -0.0451  Do you ship internationally?
```

"Login credentials" shares no words with "reset my password", and it still ranks first.
The model is `all-MiniLM-L6-v2` (`minilm-l6-v2`, 88 MB), downloaded on first use, and its
vectors match sentence-transformers to four decimal places.

**Write-up:** [Semantic Search in Python without PyTorch](https://kjarni.ai/blog/semanticsearchpython/)

Python 3.8 or newer on Linux x64 and arm64, macOS on Apple Silicon, and Windows x64.
