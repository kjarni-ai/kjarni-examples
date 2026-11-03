# Sentiment analysis in C# with transformer models

Classify text as positive, negative or neutral, and by emotion, in C#, with no Python and
no cloud API. One NuGet package; the models run on your CPU.

```bash
cd sentiment-analysis-csharp
dotnet run
dotnet run -- "The battery died after two hours"
```

```
Sentiment (roberta-sentiment):
  positive (98.5%)   "I love this product!"
  negative (94.1%)   "Terrible quality, broke after one day."
  positive (52.9%)   "It's okay I guess."
  positive (97.2%)   "Fast shipping, great product"
  neutral (82.0%)    "Does what it says"

Emotion (distilroberta-emotion):
  joy (97.0%)        "I love this product!"
  fear (58.8%)       "Terrible quality, broke after one day."
  ...
```

Other models work the same way: `bert-sentiment-multilingual` (1 to 5 stars, six
languages), `toxic-bert` (toxicity), `roberta-emotions` (28 emotions).

**Write-up:** [Sentiment Analysis in C#](https://kjarni.ai/blog/sentimentanalysis/)

Requires the [.NET 8 SDK](https://dotnet.microsoft.com/download).
