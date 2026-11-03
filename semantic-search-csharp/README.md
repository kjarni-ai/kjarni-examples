# Semantic search in C#: match text by meaning

Find the closest text by meaning rather than by shared words, in C#, with a sentence
embedding model running in your own process. One NuGet package, no API key, no vector
database.

```bash
cd semantic-search-csharp
dotnet run
dotnet run -- where is my package
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
vectors match sentence-transformers in Python.

**Write-up:** [Semantic Search in C#](https://kjarni.ai/blog/semanticsearch/).
For files on disk with keyword, semantic and hybrid search, see
[Document Search in C#](https://kjarni.ai/blog/documentsearchengine/).

Requires the [.NET 8 SDK](https://dotnet.microsoft.com/download).
