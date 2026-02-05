#ifndef INPUT_EVENT_HANDLER_HPP
#define INPUT_EVENT_HANDLER_HPP

#include <cstdint>
#include <string>

void handleChar(std::string input, unsigned char c);
void readNextChars(uint8_t len);

#endif
