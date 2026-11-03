#!/bin/sh
# Ranks five support questions by meaning against a query, using only the kjarni CLI.
query="${*:-I need to change my login credentials}"

# Fetch the model up front; a no-op once it is cached.
kjarni model download minilm-l6-v2 >/dev/null

echo "query: \"$query\""
while IFS= read -r doc; do
    printf '  %7.4f  %s\n' "$(kjarni similarity -q "$query" "$doc")" "$doc"
done <<DOCS | sort -k1 -rn
How do I reset my password?
What is your refund policy?
Do you ship internationally?
How do I update my billing address?
Where can I track my order?
DOCS
