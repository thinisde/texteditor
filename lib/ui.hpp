#pragma once
#ifndef UI_HPP
#define UI_HPP

#include "../class/state.hpp"
#include <string>

void drawStatusLine(const std::string &text);
void clearStatusLine();
void clearScreen();
int getTerminalRows();
std::string createStatusLine(State &state);

#endif
