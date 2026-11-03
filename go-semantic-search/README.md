# Semantic search in Go without cgo

Rank text by meaning from Go with a sentence embedding model running in your own process.
`kjarni-go` loads the native library through purego, so there is no cgo and no C
toolchain to install.

```bash
cd go-semantic-search
go run .
go run . where is my package
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
scores are the same as in every other language in this repository.

Package docs: [pkg.go.dev/github.com/olafurjohannsson/kjarni-go](https://pkg.go.dev/github.com/olafurjohannsson/kjarni-go).
Go 1.22 or newer.
