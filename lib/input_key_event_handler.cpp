#include "input_key_event_handler.hpp"

void moveCursorDown(State &state) {
  size_t cur = state.cursor;
  size_t len = state.input.size();

  while (cur > 0 && state.input[cur - 1] != '\n')
    cur--;
  size_t col = state.cursor - cur;

  size_t line_end = state.cursor;
  while (line_end < len && state.input[line_end] != '\n')
    line_end++;
  if (line_end == len)
    return;

  size_t next_start = line_end + 1;

  size_t next_end = next_start;
  while (next_end < len && state.input[next_end] != '\n')
    next_end++;

  state.cursor = next_start + std::min(col, next_end - next_start);
}

void moveCursorUp(State &state) {
  if (state.cursor == 0)
    return;

  size_t cur = state.cursor;
  while (cur > 0 && state.input[cur - 1] != '\n')
    cur--;
  if (cur == 0)
    return;

  size_t col = state.cursor - cur;

  size_t prev_end = cur - 1;
  size_t prev_start = prev_end;
  while (prev_start > 0 && state.input[prev_start - 1] != '\n')
    prev_start--;

  size_t prev_len = prev_end - prev_start + 1;
  state.cursor = prev_start + std::min(col, prev_len);
}

void handleESC(State &state) {
  if (state.getState() > 0) {
    state.setState(0);
  }
}

void handleInsert(State &state, unsigned char c) {
  if (state.getState() == 1) {
    state.input.insert(state.cursor, 1, c);
    state.cursor++;
  }
  if (state.getState() == 0) {
    switch (c) {
    case 105:
      state.setState(1);
      break;
    case 58:
      state.setState(2);
      break;
    case 108:
      if (state.cursor < state.input.size())
        state.cursor++;
      break;
    case 104:
      if (state.cursor > 0)
        state.cursor--;
      break;
    case 106:
      moveCursorDown(state);
      break;
    case 107:
      moveCursorUp(state);
      break;
    }
  }
  if (state.getState() == 2) {
    std::string newCommand = state.getCommand();
    newCommand += c;
    state.setCommand(newCommand);
  }
}

void moveCursorLeft(State &state) {
  if (state.cursor > 0) {
    state.cursor--;
  }
}

void moveCursorRight(State &state) {
  if (state.cursor < state.input.size()) {
    state.cursor++;
  }
}

void handleDelete(State &state) {
  if (state.getState() == 2) {
    std::string newCommand = state.getCommand();
    if (newCommand.length() > 0) {
      newCommand.erase(newCommand.length() - 1, 1);
    }
    state.setCommand(newCommand);
    return;
  }
  if (state.cursor > 0) {
    state.input.erase(state.cursor - 1, 1);
    state.cursor--;
  }
}

int handleEnter(State &state) {
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
    state.input.insert(state.cursor, 1, '\n');
    state.cursor++;
    return 0;
  }
  default:
    return 0;
  }
}
