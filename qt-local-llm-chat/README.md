# Local LLM in Qt: an offline chat app in QML and C++

A Qt 6 / QML chat window that runs Llama 3.2 1B inside the application: tokens stream into
the UI, generation can be stopped, and the conversation keeps its history. No server and
no API key.

```bash
cd qt-local-llm-chat
mkdir kjarni-lib
curl -sL https://github.com/olafurjohannsson/kjarni/releases/latest/download/kjarni-x86_64-linux.tar.gz \
  | tar xz -C kjarni-lib

cmake -B build -DCMAKE_PREFIX_PATH=$HOME/Qt/6.8.3/gcc_64 -DKJARNI_DIR=$PWD/kjarni-lib
cmake --build build && ./build/kjarni_qt_chat
```

Needs Qt 6.5 or later with Qt Quick; tested with 6.8.3. Point `CMAKE_PREFIX_PATH` at your
Qt installation.

**Write-up, with timings and memory use:**
[Local LLM in Qt](https://kjarni.ai/blog/qtchat/)
