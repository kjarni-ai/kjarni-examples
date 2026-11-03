package main

import (
	"fmt"
	"os"
	"sort"
	"strings"

	kjarni "github.com/olafurjohannsson/kjarni-go"
)

func main() {
	docs := []string{
		"How do I reset my password?",
		"What is your refund policy?",
		"Do you ship internationally?",
		"How do I update my billing address?",
		"Where can I track my order?",
	}

	query := "I need to change my login credentials"
	if len(os.Args) > 1 {
		query = strings.Join(os.Args[1:], " ")
	}

	e, err := kjarni.NewEmbedder("minilm-l6-v2")
	if err != nil {
		fmt.Fprintln(os.Stderr, "could not load model:", err)
		os.Exit(1)
	}
	defer e.Close()

	type hit struct {
		score float32
		doc   string
	}
	var hits []hit
	for _, d := range docs {
		s, err := e.Similarity(query, d)
		if err != nil {
			fmt.Fprintln(os.Stderr, "similarity failed:", err)
			os.Exit(1)
		}
		hits = append(hits, hit{s, d})
	}
	sort.Slice(hits, func(i, j int) bool { return hits[i].score > hits[j].score })

	fmt.Printf("query: %q\n", query)
	for _, h := range hits {
		fmt.Printf("  %7.4f  %s\n", h.score, h.doc)
	}
}
