# Image search in C#: find photos by description with CLIP, offline

Type "a dog on a beach" and get back the photos of a dog on a beach, from a folder nobody
has tagged. Runs CLIP inside your .NET process with [Kjarni](https://github.com/olafurjohannsson/kjarni):
no cloud vision API, no Python, no ONNX export.

```bash
cd image-search-csharp
dotnet run -- ~/Pictures
```

```
Indexing /home/me/Pictures, this takes a moment the first time...
Indexed 997 photos, skipped 3

Search: a dog on a beach
  0.311  /home/me/Pictures/000000052891.jpg
  0.227  /home/me/Pictures/000000050326.jpg
  ...
```

The first run downloads the CLIP model (580 MB) and indexes the folder, about 25 ms per
photo on a desktop CPU. The index is saved beside the photos as `.photos.kjimg`, so later
runs start searching at once. An empty line quits.

Scores are cosine similarities and are small even for good matches (0.2 to 0.35); only the
order matters. JPEG and PNG are indexed; HEIC, WebP and RAW are not.

**Write-up, with accuracy measured on 1,000 COCO photos:**
[Image Search in C# with CLIP](https://kjarni.ai/blog/imagesearch/)

Requires the [.NET 8 SDK](https://dotnet.microsoft.com/download). Works on Windows x64,
Linux x64 and arm64, and macOS on Apple Silicon.
