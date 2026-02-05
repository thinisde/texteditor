#include "input_key_event_handler.hpp"

void handleESC(State &state) {
  if (state.getState() > 0) {
    state.setState(0);
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
      state.setState(1);
      break;
    case 58:
      state.setState(2);
      break;
    }
  }
  if (state.getState() == 2) {
    std::string newCommand = state.getCommand();
    newCommand += c;
    state.setCommand(newCommand);
  }
}

void handleDelete(State &state, std::string &input, size_t &cursor) {
  if (state.getState() == 2) {
    std::string newCommand = state.getCommand();
    if (newCommand.length() > 0) {
      newCommand.erase(newCommand.length() - 1, 1);
    }
    state.setCommand(newCommand);
    return;
  }
  if (cursor > 0) {
    input.erase(cursor - 1, 1);
    cursor--;
  }
}

int handleEnter(State &state, std::string &input, size_t &cursor) {
  switch (state.getState()) {
  case 2: {
    state.setState(0);
    if (state.getCommand() == ":q!") {
      return 1;
    }
    state.setCommand("");
    return 0;
  }
  case 1: {
    input.insert(cursor, 1, '\n');
    cursor++;
    return 0;
  }
  default:
    return 0;
  }
}
