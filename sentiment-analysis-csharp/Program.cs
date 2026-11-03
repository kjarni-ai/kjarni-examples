using Kjarni;

var texts = args.Length > 0 ? args : new[] {
    "I love this product!",
    "Terrible quality, broke after one day.",
    "It's okay I guess.",
    "Fast shipping, great product",
    "Does what it says",
};

using var sentiment = new Classifier("roberta-sentiment");
Console.WriteLine("Sentiment (roberta-sentiment):");
foreach (var text in texts)
    Console.WriteLine($"  {sentiment.Classify(text),-18} \"{text}\"");

using var emotion = new Classifier("distilroberta-emotion");
Console.WriteLine("\nEmotion (distilroberta-emotion):");
foreach (var text in texts)
    Console.WriteLine($"  {emotion.Classify(text),-18} \"{text}\"");
