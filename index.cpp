#include "class/state.hpp"
#include "lib/input_event_handler.hpp"
#include "lib/input_handler.hpp"
#include "lib/ui.hpp"
#include <iostream>
#include <unistd.h>

int main(int argc, char **argv) {
  clearScreen();
  enableRawMode();

  State state;

  if (argc > 1) {
    if (!loadFile(state, argv[1])) {
      state.input = "";
      state.path = "untitled";
    } else {
      state.path = argv[1];
      state.cursor = 0;
    }
  }

  drawStatusLine(createStatusLine(state));
  redraw(state.input, state.cursor);

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
  std::cout << std::endl;
  return 0;
}
