#include "input_event_handler.hpp"
#include "input_key_event_handler.hpp"
#include <cstdint>
#include <iostream>
#include <poll.h>
#include <string>
#include <unistd.h>

static bool readByteWithTimeout(unsigned char &out, int timeout_ms) {
  pollfd pfd{};
  pfd.fd = STDIN_FILENO;
  pfd.events = POLLIN;

  int r = ::poll(&pfd, 1, timeout_ms);
  if (r <= 0)
    return false; // timeout or error

  ssize_t n = ::read(STDIN_FILENO, &out, 1);
  return n == 1;
}

static std::string readEscapeSequence() {
  // After ESC, arrow keys usually send: '[' then a final letter.
  unsigned char b1;
  if (!readByteWithTimeout(b1, 30))
    return {}; // no follow-up => plain ESC

  std::string seq;
  seq.push_back((char)b1);

  // For CSI sequences, read one more byte (C/D/A/B). Good enough for arrows.
  if (b1 == '[') {
    unsigned char b2;
    if (readByteWithTimeout(b2, 5))
      seq.push_back((char)b2);
  }

  return seq; // e.g. "[" "C" or empty for plain ESC
}

static std::string readNextChars(uint8_t len) {
  std::string seq(len, '\0');
  for (uint8_t i = 0; i < len; i++) {
    ssize_t n = ::read(STDIN_FILENO, &seq[i], 1);
    if (n <= 0)
      return {};
  }

  return seq;
};

int handleEvent(State &state, std::string &input, size_t &cursor) {
  unsigned char c;
  ssize_t n = ::read(STDIN_FILENO, &c, 1);

  if (n <= 0)
    return 0;

  switch (c) {
  case '\r':
  case '\n':
    return 1;
  case 27: {
    std::string seq = readEscapeSequence();

    if (seq.empty()) {
      handleESC(state);
      break;
    }

    if (seq.size() >= 2 && seq[0] == '[') {
      if (seq[1] == 'C' && cursor < input.size())
        cursor++;
      else if (seq[1] == 'D' && cursor > 0)
        cursor--;
    }
    break;
  }
  case 127:
  case 8:
    handleDelete(state, input, cursor);
    break;
  default:
    if (c >= 32 && c <= 126) {
      handleInsert(state, input, cursor, c);
    }
    break;
  }

  return 0;
};
