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
    state.path = argv[1];
    if (!loadFile(state)) {
      state.input.clear();
    }
  } else {
    state.path = "untitled";
  }

  drawStatusLine(createStatusLine(state));
  redraw(state.input, state.cursor);
  std::cout << std::flush;

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
