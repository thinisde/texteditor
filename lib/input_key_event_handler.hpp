#pragma once
#ifndef INPUT_KEY_EVENT_HANDLER_HPP
#define INPUT_KEY_EVENT_HANDLER_HPP

#include "../class/state.hpp"
#include <stddef.h>
#include <string>

void handleESC(State &state);

void handleInsert(State &state, unsigned char c);

void handleDelete(State &state);
int handleEnter(State &state);

void handleDoublePoints(State &state, unsigned char c);

void moveCursorUp(State &state);
void moveCursorDown(State &state);
void moveCursorLeft(State &state);
void moveCursorRight(State &state);

#endif
