using Kjarni;

// Downloads the model on first use (about 2 GB), then runs offline.
using var chat = new Chat("llama3.2-3b-instruct",
    systemPrompt: "You are a helpful assistant. Keep answers short.",
    quiet: true);

var convo = chat.Conversation();

Console.WriteLine("Chat with a local Llama 3.2 3B. An empty line quits.");
while (true)
{
    Console.Write("\n> ");
    var line = Console.ReadLine();
    if (string.IsNullOrWhiteSpace(line)) break;

    convo.Stream(line, token =>
    {
        Console.Write(token);
        return true;   // return false to stop generating
    });
    Console.WriteLine();
}
