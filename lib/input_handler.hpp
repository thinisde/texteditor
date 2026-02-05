#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <cstddef>
#include <string>

void disableRawMode();
void handleSignal(int signal);
void enableRawMode();

void redraw(const std::string &s, size_t cursor);

#endif
