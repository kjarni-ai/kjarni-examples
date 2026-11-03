# Kjarni examples

Runnable examples for [Kjarni](https://github.com/olafurjohannsson/kjarni), a native engine
that runs transformer models inside your own process: embeddings, search, classification,
image search and local LLM chat, from C#, C++, Python, Go, Rust and the browser. Everything
runs on your machine and works offline once a model has downloaded.

| Example | What it does | Language |
|---|---|---|
| [python-semantic-search](python-semantic-search/) | Match text by meaning, no PyTorch | Python |
| [python-image-search](python-image-search/) | Search a photo folder by description with CLIP | Python |
| [semantic-search-csharp](semantic-search-csharp/) | Match text by meaning with sentence embeddings | C# |
| [image-search-csharp](image-search-csharp/) | Search a photo folder by description with CLIP | C# |
| [local-llm-csharp](local-llm-csharp/) | Chat with Llama 3.2 in-process, no Ollama, no API key | C# |
| [sentiment-analysis-csharp](sentiment-analysis-csharp/) | Sentiment and emotion with transformer models | C# |
| [cpp-semantic-search](cpp-semantic-search/) | Semantic search without libtorch or ONNX Runtime | C++ |
| [qt-local-llm-chat](qt-local-llm-chat/) | An offline LLM chat app in Qt 6 / QML | C++ / Qt |
| [go-semantic-search](go-semantic-search/) | Match text by meaning, no cgo | Go |
| [rust-semantic-search](rust-semantic-search/) | Match text by meaning | Rust |
| [browser-semantic-search](browser-semantic-search/) | Match text by meaning in a web page, via WebAssembly | JavaScript |
| [cli-semantic-search](cli-semantic-search/) | Match text by meaning from a shell script | CLI |

Each folder has a README with the commands to run it and the output it prints. The
semantic search examples use the same five sentences and the same model, so their scores
can be compared: every native binding prints identical numbers. Models download on first
use and are cached.

Every example except the Qt app and the browser page is built and run in CI against the
published packages.

More at [kjarni.ai](https://kjarni.ai), with a [blog](https://kjarni.ai/blog/) that walks
through each of these in detail.

MIT licensed.
