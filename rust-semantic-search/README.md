# Semantic search in Rust

Rank text by meaning in Rust with a sentence embedding model. The engine is a Rust crate:
no libtorch, no ONNX Runtime, no Python.

```bash
cd rust-semantic-search
cargo run --release
cargo run --release -- where is my package
```

```
query: "I need to change my login credentials"
   0.5981  How do I reset my password?
   0.4067  How do I update my billing address?
   0.0767  Where can I track my order?
  -0.0027  What is your refund policy?
  -0.0451  Do you ship internationally?
```

The model is `all-MiniLM-L6-v2` (`minilm-l6-v2`, 88 MB), downloaded on first use. The
first build compiles the engine and takes a few minutes.

Crate docs: [docs.rs/kjarni](https://docs.rs/kjarni).
