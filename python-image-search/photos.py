import sys
from pathlib import Path

from kjarni import ImageIndex

folder = Path(sys.argv[1])
query = " ".join(sys.argv[2:]) or "a dog on the beach"
saved = folder / ".photos.kjimg"

index = ImageIndex()
if saved.exists():
    index.load(str(saved))
else:
    report = index.add_directory(str(folder))
    print(f"indexed {report.added} photos, skipped {report.skipped}")
    index.save(str(saved))

print(f'query: "{query}"')
for hit in index.search(query, top_k=5):
    print(f"  {hit.score:.4f}  {hit.path}")
