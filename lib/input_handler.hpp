#pragma once
#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include "../class/state.hpp"
#include <cstddef>
#include <string>

void disableRawMode();
void handleSignal(int signal);
void enableRawMode();

bool loadFile(State &state);
bool saveFile(State &state);

void indexToRowCol(std::string s, size_t idx, int &row, int &col);

void redraw(const std::string &s, size_t cursor);

#endif
