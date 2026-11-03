# Local LLM chat in C#, without Ollama or an API key

Chat with Llama 3.2 3B from a C# console app. The model runs inside your process: no
Ollama daemon, no localhost port, no API key, and offline once it has downloaded.

```bash
cd local-llm-csharp
dotnet run
```

```
Chat with a local Llama 3.2 3B. An empty line quits.

> What is the capital of Iceland?
The capital of Iceland is Reykjavik.

> My name is Olafur. What is my name?
Your name is Olafur.
```

Replies stream token by token, and the conversation keeps its history. The first run
downloads the model, about 2 GB. Llama is gated on Hugging Face, so set `HF_TOKEN` after
accepting its licence, or switch to `qwen2.5-1.5b-instruct`, which needs no token.

**Write-up:** [Local LLM Chat in C#](https://kjarni.ai/blog/localchat/). For
Microsoft.Extensions.AI, see [a local IChatClient](https://kjarni.ai/blog/ichatclient/).

Requires the [.NET 8 SDK](https://dotnet.microsoft.com/download).
