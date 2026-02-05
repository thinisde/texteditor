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

  State state;

  drawStatusLine(createStatusLine(state));

  while (true) {
    int done = handleEvent(state);

    redraw(state.input, state.cursor);

    drawStatusLine(createStatusLine(state));

    if (done) {
      clearStatusLine();
      break;
    }
  }

  disableRawMode();
  std::cout << "\nYou entered: " << state.input << std::endl;
  return 0;
}
