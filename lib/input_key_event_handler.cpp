#include "input_key_event_handler.hpp"

void handleESC(State &state) {
  if (state.getState() == 1) {
    state.toggleState();
  }
}

void handleInsert(State &state, std::string &input, size_t &cursor,
                  unsigned char c) {
  if (state.getState() == 1) {
    input.insert(cursor, 1, c);
    cursor++;
  }
  if (state.getState() == 0) {
    switch (c) {
    case 105:
      state.toggleState();
      break;
    }
  }
  if (state.getState() == 2) {
    std::string newCommand = "";
    newCommand += c;
    state.setCommand(newCommand);
  }
}

void handleDelete(State &state, std::string &input, size_t &cursor) {
  if (cursor > 0) {
    input.erase(cursor - 1, 1);
    cursor--;
  }
}
