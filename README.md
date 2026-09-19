# Minimizing Space Requirement for Disk Servers

A C++ implementation of **Huffman Coding** for lossless data compression, developed to reduce storage requirements by assigning shorter binary codes to frequently occurring characters and longer codes to less frequent ones. 

## Features

- Reads text input and calculates character frequencies
- Builds a **Min Heap** and constructs a Huffman Tree
- Generates variable-length prefix codes
- Encodes text using Huffman codes
- Decodes binary data back to the original text
- Uses `unordered_map` for frequency and code storage :contentReference[oaicite:1]{index=1}

## How It Works

1. Calculate the frequency of each character.
2. Insert characters into a Min Heap.
3. Repeatedly combine the two least-frequent nodes to build the Huffman Tree.
4. Assign `0` to left edges and `1` to right edges.
5. Use the generated prefix codes for encoding and decoding. 

## Example

For one sample containing **190 characters**, Huffman Coding required **622 bits**, compared with **760 bits** using fixed-length encoding, saving **138 bits**.

## Tech Stack

- C++
- Data Structures
- Min Heap
- Binary Trees
- Hash Maps
- File I/O

## Authors
- Ritwika Pal

Developed under the guidance of **Prof. Biswajit Sahoo**, KIIT University.
