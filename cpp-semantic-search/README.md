# Semantic search in C++ without libtorch or ONNX Runtime

Rank text by meaning from C++, with one header and one shared library that links only
against libc.

```bash
cd cpp-semantic-search
curl -sL https://github.com/olafurjohannsson/kjarni/releases/latest/download/kjarni-x86_64-linux.tar.gz | tar xz
g++ -std=c++23 search.cpp -I. -L. -lkjarni_ffi -Wl,-rpath,'$ORIGIN' -o search && ./search
```

```
query: "I need to change my login credentials"
  0.5981  How do I reset my password?
  0.4067  How do I update my billing address?
  0.0767  Where can I track my order?
  -0.0027  What is your refund policy?
  -0.0451  Do you ship internationally?
```

`kjarni.hpp` needs C++23 (GCC 14 or Clang 18 and newer) for `std::expected` and `std::print`. `kjarni.h` is a plain C API that works from
C++11. Archives for macOS, Linux arm64 and Windows are on the
[releases page](https://github.com/olafurjohannsson/kjarni/releases).

**Write-up:** [Local Semantic Search in C++](https://kjarni.ai/blog/cppinference/)
