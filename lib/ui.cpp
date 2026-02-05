#include "ui.hpp"

#include "../class/state.hpp"
#include "input_handler.hpp"
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

int getTerminalRows() {
  winsize w{};
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return (w.ws_row > 0) ? (int)w.ws_row : 24;
}

void drawStatusLine(const std::string &text) {
  int rows = getTerminalRows();

  // Save cursor position
  std::cout << "\033[s";

  // Move to bottom row, column 1
  std::cout << "\033[" << rows << ";1H";

  // Clear the line
  std::cout << "\033[2K";

  // Style (optional)
  std::cout << "\033[7m"; // inverse colors

  // Write text (trim if too long)
  std::cout << " " << text;

  // Reset style
  std::cout << "\033[0m";

  // Restore cursor position
  std::cout << "\033[u" << std::flush;
}

std::string createStatusLine(State &state) {
  std::string mode = "VIEW";

  switch (state.getState()) {
  case 0:
    mode = "VIEW";
    break;
  case 1:
    mode = "INSERT";
    break;
  case 2:
    mode = "CMD";
    break;
  }

  (state.getCommand().length() > 0 ? state.getCommand() : "");
  if (state.getCommand().length() > 0) {
    return state.getCommand();
  }
  return mode + " |  " + state.path +
         " | Len: " + std::to_string(state.input.size());
}

void clearStatusLine() {
  // Save cursor
  std::cout << "\033[s";

  // Move to bottom row, column 1
  std::cout << "\033[" << getTerminalRows() << ";1H";

  // Clear entire line
  std::cout << "\033[2K";

  // Restore cursor
  std::cout << "\033[u" << std::flush;
}

void clearScreen() { std::cout << "\033[2J\033[H" << std::flush; }
