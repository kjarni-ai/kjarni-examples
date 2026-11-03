use kjarni::Embedder;

#[tokio::main]
async fn main() -> anyhow::Result<()> {
    let docs = [
        "How do I reset my password?",
        "What is your refund policy?",
        "Do you ship internationally?",
        "How do I update my billing address?",
        "Where can I track my order?",
    ];

    let args: Vec<String> = std::env::args().skip(1).collect();
    let query = if args.is_empty() {
        "I need to change my login credentials".to_string()
    } else {
        args.join(" ")
    };

    let embedder = Embedder::new("minilm-l6-v2").await?;
    let ranked = embedder.rank_by_similarity(&query, &docs).await?;

    println!("query: \"{query}\"");
    for (i, score) in ranked {
        println!("  {score:7.4}  {}", docs[i]);
    }
    Ok(())
}
