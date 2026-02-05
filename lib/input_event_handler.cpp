#include "input_event_handler.hpp"
#include "input_key_event_handler.hpp"
#include <cstdint>
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
  unsigned char b1;
  if (!readByteWithTimeout(b1, 30))
    return {};

  std::string seq;
  seq.push_back((char)b1);

  if (b1 == '[') {
    unsigned char b2;
    if (readByteWithTimeout(b2, 5))
      seq.push_back((char)b2);
  }

  return seq;
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

int handleEvent(State &state) {
  unsigned char c;
  ssize_t n = ::read(STDIN_FILENO, &c, 1);

  if (n <= 0)
    return 0;
  switch (c) {
  case '\r':
  case '\n':
    return handleEnter(state);
  case 27: {
    std::string seq = readEscapeSequence();

    if (seq.empty()) {
      handleESC(state);
      break;
    }

    if (seq.size() >= 2 && seq[0] == '[') {
      if (seq == "[D")
        moveCursorLeft(state);
      if (seq == "[C")
        moveCursorRight(state);
      if (seq == "[A")
        moveCursorUp(state);
      if (seq == "[B")
        moveCursorDown(state);
    }

    break;
  }
  case 127:
  case 8:
    handleDelete(state);
    break;
  default:
    if (c >= 32 && c <= 126) {
      handleInsert(state, c);
    }
    break;
  }

  return 0;
};
