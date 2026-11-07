# Minimizing Space Requirement for Disk Servers

A C++ implementation of **Huffman Coding** for lossless data compression, developed to reduce storage requirements by assigning shorter binary codes to frequently occurring characters and longer codes to less frequent ones. 
An interactive lossless text compression visualizer has been built to provide a user experience.

## Website

https://ritwika101.github.io/minimizing-space-requirement-for-disk-server/

## Features

- Reads text input and calculates character frequencies
- Builds a **Min Heap** and constructs a Huffman Tree
- Generates variable-length prefix codes
- View character frequencies and binary codes
- Inspect the binary Huffman tree and its 0/1 branches
- Examine the encoded bitstream and decoded text
- Compare original 8-bit text size with encoded data-bit length
- Decodes binary data back to the original text

## How It Works

1. Calculate the frequency of each character.
2. Insert characters into a Min Heap.
3. Repeatedly combine the two least-frequent nodes to build the Huffman Tree.
4. Assign `0` to left edges and `1` to right edges.
5. Use the generated prefix codes for encoding and decoding. 

## Technology

C++, WebAssembly (Emscripten), HTML, CSS, JavaScript. 

## Local build

Install [Emscripten](https://emscripten.org/docs/getting_started/downloads.html), activate the SDK, then execute:

```bash
bash build.sh
python3 -m http.server 8000 --directory site
```

Open `http://localhost:8000`.


## Notes

The program supports file-based encoding/decoding; the interactive visualizer takes text input and runs the compression logic in browser memory. Unicode text is processed as UTF-8 bytes. The compression statistics are educational, not a full archive file-size estimate.

## Author

**Ritwika Pal**
