// Browser adapter. The original Huffman.cpp is included unchanged.
#include <cstdlib>
#define main original_file_based_main
#include "Huffman.cpp"
#undef main

#include <sstream>
#include <vector>
#include <map>
#include <stdexcept>
#include <iomanip>
#include <cctype>
#include <cstdlib>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define WEB_EXPORT EMSCRIPTEN_KEEPALIVE
#else
#define WEB_EXPORT
#endif

static std::string jsonEscape(const std::string &s) {
  std::ostringstream out;
  for (unsigned char c : s) {
    switch (c) {
      case '\"': out << "\\\""; break;
      case '\\': out << "\\\\"; break;
      case '\n': out << "\\n"; break;
      case '\r': out << "\\r"; break;
      case '\t': out << "\\t"; break;
      default:
        if (c < 0x20) { out << "\\u00" << std::hex << std::setw(2) << std::setfill('0') << (int)c << std::dec; }
        else out << (char)c;
    }
  }
  return out.str();
}

static std::string nodeToJson(const node* p) {
  if (!p) return "null";
  std::string v = "{\"frequency\":" + std::to_string(p->freq);
  if (!p->left && !p->right) {
    v += ",\"char\":\"" + jsonEscape(std::string(1,p->a)) + "\"";
  } else {
    v += ",\"left\":" + nodeToJson(p->left) + ",\"right\":" + nodeToJson(p->right);
  }
  return v + "}";
}

// Prevent unbounded trees, bitstream display, and browser resource use.
extern "C" WEB_EXPORT const char* run_huffman(const char* input) {
  static std::string answer;
  if (!input || !*input) { answer = "{\"error\":\"Enter some text to compress.\"}"; return answer.c_str(); }
  const std::string text(input);
  if (text.size() > 3000) { answer = "{\"error\":\"Please use 3,000 bytes or fewer.\"}"; return answer.c_str(); }
  std::map<unsigned char,int> frequency;
  for (unsigned char c : text) frequency[c]++;
  if (frequency.size() > 100) { answer = "{\"error\":\"Please use 100 or fewer distinct characters.\"}"; return answer.c_str(); }

  // Reuse the existing global min-heap, tree creation, and code-generation functions.
  umap.clear();
  std::vector<node*> heap;
  for (const auto &entry : frequency) heap.push_back(buildNode(entry.second, static_cast<char>(entry.first)));
  n = static_cast<int>(heap.size());
  std::ostringstream originalConsole;
  std::streambuf* old = std::cout.rdbuf(originalConsole.rdbuf());
  buildHeap(heap.data());
  Huffman(heap.data());
  int arr[256] = {};
  Codes(heap[0], arr, 0);
  std::cout.rdbuf(old);

  // A single symbol has a depth-zero tree; give it a 1-bit code for display.
  if (frequency.size() == 1) umap.begin()->second = "0";

  std::string encoded;
  for (unsigned char c : text) encoded += umap[static_cast<char>(c)];

  // Decode by traversing the exact same Huffman tree.
  std::string decoded;
  if (frequency.size() == 1) decoded.assign(encoded.size(), text[0]);
  else {
    const node *cur = heap[0];
    for (char b : encoded) {
      cur = b == '0' ? cur->left : cur->right;
      if (!cur) break;
      if (!cur->left && !cur->right) {decoded += cur->a; cur = heap[0];}
    }
  }
  const bool matches = decoded == text;
  std::ostringstream result;
  result << "{\"originalBytes\":" << text.size() << ",\"originalBits\":" << text.size()*8
         << ",\"encodedBits\":" << encoded.size()
         << ",\"encoded\":\"" << encoded << "\""
         << ",\"decoded\":\"" << jsonEscape(decoded) << "\""
         << ",\"roundTrip\":" << (matches?"true":"false")
         << ",\"tree\":" << nodeToJson(heap[0]) << ",\"codes\":[";
  bool first = true;
  for (const auto &entry : frequency) {
    if (!first) result << ',';
    first = false;
    result << "{\"char\":\"" << jsonEscape(std::string(1, static_cast<char>(entry.first)))
           << "\",\"frequency\":" << entry.second << ",\"code\":\""
           << umap[static_cast<char>(entry.first)] << "\"}";
  }
  result << "]}";
  answer = result.str();
  return answer.c_str();
}

#ifndef __EMSCRIPTEN__
int main(int argc, char** argv) {
  std::string s = argc > 1 ? argv[1] : "BANANA";
  puts(run_huffman(s.c_str()));
}
#endif
