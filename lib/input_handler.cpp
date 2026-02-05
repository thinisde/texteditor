#include "input_handler.hpp"
#include <csignal>
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

static termios g_orig;

void disableRawMode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_orig); }
void handleSignal(int signal) {
  disableRawMode();
  std::cout << std::endl;
  std::exit(signal);
}

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &g_orig);
  std::atexit(disableRawMode);
  std::signal(SIGINT, handleSignal);
  std::signal(SIGTERM, handleSignal);

  termios raw = g_orig;

  raw.c_lflag &= ~(ECHO | ICANON);
  raw.c_lflag &= ~(ISIG);

  raw.c_iflag &= ~(IXON | ICRNL);

  raw.c_cflag |= (CS8);

  raw.c_cc[VMIN] = 1;
  raw.c_cc[VTIME] = 0;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

static void cursorRowColFromIndex(const std::string &s, size_t idx, int &row,
                                  int &col) {
  row = 1;
  col = 1;
  idx = std::min(idx, s.size());

  for (size_t i = 0; i < idx; i++) {
    if (s[i] == '\n') {
      row++;
      col = 1;
    } else {
      col++;
    }
  }
}

void redraw(const std::string &s, size_t cursor) {
  // Clear screen and go home
  std::cout << "\033[2J\033[H";

  // Print buffer
  std::cout << s;

  // Compute cursor position
  int row, col;
  cursorRowColFromIndex(s, cursor, row, col);

  // Move cursor there
  std::cout << "\033[" << row << ";" << col << "H" << std::flush;
}
