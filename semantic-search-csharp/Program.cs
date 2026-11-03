using Kjarni;

using var embedder = new Embedder("minilm-l6-v2");

var docs = new[] {
    "How do I reset my password?",
    "What is your refund policy?",
    "Do you ship internationally?",
    "How do I update my billing address?",
    "Where can I track my order?",
};

// Encode the documents once and keep the vectors.
var vectors = embedder.EncodeBatch(docs);

var query = args.Length > 0 ? string.Join(' ', args) : "I need to change my login credentials";
var q = embedder.Encode(query);

Console.WriteLine($"query: \"{query}\"");
foreach (var (doc, score) in docs
             .Select((doc, i) => (doc, score: Embedder.CosineSimilarity(q, vectors[i])))
             .OrderByDescending(x => x.score))
    Console.WriteLine($"  {score,7:F4}  {doc}");
