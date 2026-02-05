#pragma once
#include <cstdint>
#include <string>

class State {
public:
  State();
  uint8_t getState() const;
  void setState(uint8_t state);
  void setCommand(std::string newCommand);
  const std::string &getCommand() const;

  size_t cursor = 0;
  std::string input;

private:
  uint8_t currentState = 0;
  std::string command;
};
