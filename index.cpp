#include "class/state.hpp"
#include "lib/input_event_handler.hpp"
#include "lib/input_handler.hpp"
#include "lib/misc.hpp"
#include "lib/ui.hpp"
#include <iostream>
#include <unistd.h>

int main() {
  clearScreen();
  enableRawMode();

  std::string input;
  size_t cursor = 0;

  State state;

  drawStatusLine(createStatusLine(state, input));

  while (true) {
    int done = handleEvent(state, input, cursor);

    redraw(input, cursor);

    drawStatusLine(createStatusLine(state, input));

    if (done) {
      clearStatusLine();
      break;
    }
  }

  disableRawMode();
  std::cout << "\nYou entered: " << input << std::endl;
  return 0;
}
