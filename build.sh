#!/usr/bin/env bash
set -euo pipefail
mkdir -p site
em++ cpp/web_bridge.cpp -std=c++17 -O2 \
  -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s ENVIRONMENT=web \
  -s MODULARIZE=1 -s EXPORT_NAME=createHuffmanModule \
  -s EXPORTED_FUNCTIONS='["_run_huffman"]' \
  -s EXPORTED_RUNTIME_METHODS='["ccall"]' \
  -o site/huffman.js
