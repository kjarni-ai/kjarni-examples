# Semantic search in the browser with WebAssembly

Rank text by meaning on a web page with the model running in the browser. Nothing is
installed and nothing you type leaves the page. One HTML file, no build step.

```bash
cd browser-semantic-search
python3 -m http.server 8000    # then open http://localhost:8000
```

```
query: "I need to change my login credentials"
   0.5779  How do I reset my password?
   0.4040  How do I update my billing address?
   0.0928  Where can I track my order?
   0.0188  What is your refund policy?
  -0.0457  Do you ship internationally?
```

Type in the box and the list re-ranks on each keystroke. The page loads
[kjarni-wasm](https://www.npmjs.com/package/kjarni-wasm) from a CDN and a 23 MB int8 copy
of `all-MiniLM-L6-v2`, which the browser caches. The int8 weights move the scores by about
0.02 from the native examples; the order is the same.

A file opened straight from disk (`file://`) cannot load the wasm module, hence the local
server. For a bundler project, `npm i kjarni-wasm` and see the
[package guide](https://github.com/olafurjohannsson/kjarni/tree/main/crates/kjarni-wasm/ts).
