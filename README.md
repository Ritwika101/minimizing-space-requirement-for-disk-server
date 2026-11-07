# Huffman Coding Visualizer

An interactive lossless text compression visualizer powered by a C++ Huffman coding implementation compiled to WebAssembly. 

## Features

- Enter text and generate variable-length Huffman codes
- View character frequencies and binary codes
- Inspect the binary Huffman tree and its 0/1 branches
- Examine the encoded bitstream and decoded text
- Compare original 8-bit text size with encoded data-bit length

The compression ratio shown excludes the metadata necessary to store or transmit the Huffman tree/codebook.

## Technology

C++, WebAssembly (Emscripten), HTML, CSS, JavaScript, SVG. 

## Local build

Install [Emscripten](https://emscripten.org/docs/getting_started/downloads.html), activate the SDK, then execute:

```bash
bash build.sh
python3 -m http.server 8000 --directory site
```

Open `http://localhost:8000`.


## Notes

The original program supports file-based encoding/decoding; the interactive visualizer takes text input and runs the compression logic in browser memory. Unicode text is processed as UTF-8 bytes. The compression statistics are educational, not a full archive file-size estimate.
