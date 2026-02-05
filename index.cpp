#include "class/state.hpp"
#include "lib/input_handler.hpp"
#include <iostream>
#include <unistd.h>

int main() {
  enableRawMode();

  std::string input;
  size_t cursor = 0;

  State *state = new State();

  std::cout << state->getState() << std::endl;

  while (true) {
    unsigned char c;

    ssize_t n = ::read(STDIN_FILENO, &c, 1);
    if (n <= 0)
      continue;

    if (c == '\r' || c == '\n') {
      break;
    }

    if (c == 27) {
      unsigned char seq[2];
      if (::read(STDIN_FILENO, &seq[0], 1) == 0)
        continue;
      if (::read(STDIN_FILENO, &seq[1], 1) == 0)
        continue;

      if (seq[0] == '[') {
        if (seq[1] == 'C') {
          if (cursor < input.size())
            cursor++;
        } else if (seq[1] == 'D') {
          if (cursor > 0)
            cursor--;
        }
      }
    } else if (c == 127 || c == 8) {
      if (cursor > 0) {
        input.erase(cursor - 1, 1);
        cursor--;
      }
    } else if (c >= 32 && c <= 126) {
      input.insert(cursor, 1, c);
      cursor++;
    } else {
    }

    redraw(input, cursor);
  }

  disableRawMode();
  std::cout << "\nYou entered: " << input << std::endl;
  return 0;
}
