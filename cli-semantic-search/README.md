# Semantic search from the command line

Compare text by meaning from a shell script with the `kjarni` command-line tool. One
binary, no Python.

```bash
curl -fsSL https://kjarni.ai/install.sh | sh
cd cli-semantic-search
./search.sh
./search.sh where is my package
```

```
query: "I need to change my login credentials"
   0.5981  How do I reset my password?
   0.4067  How do I update my billing address?
   0.0767  Where can I track my order?
  -0.0027  What is your refund policy?
  -0.0451  Do you ship internationally?
```

`kjarni similarity -q "a" "b"` prints one number, so it pipes into anything. For a folder
of documents use an index instead:

```bash
kjarni index create notes.idx ./notes
kjarni search notes.idx "how do refunds work?"
```

On Windows: `irm https://kjarni.ai/install.ps1 | iex`.

**Write-up:** [The Kjarni CLI](https://kjarni.ai/blog/cli/)
