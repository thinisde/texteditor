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

void redraw(const std::string &s, size_t cursor) {
  constexpr int prefix_len = 0;
  std::cout << "\r\033[K" << s;
  std::cout << "\r\033[" << (prefix_len + cursor) << "C";
  std::cout << std::flush;
}
