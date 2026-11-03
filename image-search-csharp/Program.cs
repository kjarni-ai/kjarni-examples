using Kjarni;

var folder = args.Length > 0 ? args[0] : Environment.GetFolderPath(Environment.SpecialFolder.MyPictures);
var indexFile = Path.Combine(folder, ".photos.kjimg");

using var index = new ImageIndex();
if (File.Exists(indexFile))
{
    Console.WriteLine($"Loaded {index.Load(indexFile)} photos from {indexFile}");
}
else
{
    Console.WriteLine($"Indexing {folder}, this takes a moment the first time...");
    var report = index.AddDirectory(folder);
    index.Save(indexFile);
    Console.WriteLine($"Indexed {report.Added} photos, skipped {report.Skipped}");
}

while (true)
{
    Console.Write("\nSearch: ");
    var query = Console.ReadLine();
    if (string.IsNullOrWhiteSpace(query)) break;

    foreach (var hit in index.Search(query, 5))
        Console.WriteLine($"  {hit.Score:F3}  {hit.Path}");
}
