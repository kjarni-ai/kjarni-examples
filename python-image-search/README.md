# Image search in Python: find photos by description with CLIP, offline

Search a folder of photos by typing what is in them, with CLIP running locally. No
PyTorch, no `transformers`, no cloud vision API; `pip install kjarni` is the only
dependency.

```bash
cd python-image-search
pip install kjarni
python photos.py ~/Pictures a dog on a beach
python photos.py ~/Pictures a plate of food
```

```
indexed 997 photos, skipped 3
query: "a dog on a beach"
  0.3110  /home/me/Pictures/000000052891.jpg
  0.2271  /home/me/Pictures/000000050326.jpg
  ...
```

The first run downloads the CLIP model (580 MB) and indexes the folder: 1,000 photos took
20 seconds on a 24-thread desktop CPU. The index is saved beside the photos as `.photos.kjimg`,
so later searches start at once.

Scores are cosine similarities and are small even for good matches (0.2 to 0.35); only the
order matters. JPEG and PNG are indexed; HEIC, WebP and RAW are skipped.

**Write-up, with accuracy measured on 1,000 COCO photos:**
[Image Search with CLIP](https://kjarni.ai/blog/imagesearch/) (the code there is C#; the
model and the results are the same).
