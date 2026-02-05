#pragma once
#ifndef INPUT_EVENT_HANDLER_HPP
#define INPUT_EVENT_HANDLER_HPP

#include "../class/state.hpp"
#include <cstdint>
#include <string>

// 0 - continue; 1 - break
int handleEvent(State &state);
static bool readByteWithTimeout(unsigned char &out, int timeout_ms);
static std::string readEscapeSequence();

#endif
