#pragma once
#ifndef INPUT_KEY_EVENT_HANDLER_HPP
#define INPUT_KEY_EVENT_HANDLER_HPP

#include "../class/state.hpp"
#include <stddef.h>
#include <string>

void handleESC(State &state);

void handleInsert(State &state, std::string &input, size_t &cursor,
                  unsigned char c);

void handleDelete(State &state, std::string &input, size_t &cursor);

void handleDoublePoints(State &state, std::string &input, size_t &cursor,
                        unsigned char c);

#endif
