#pragma once
#include <cstdint>
#include <string>

class State {
public:
  State();
  uint8_t getState() const;
  void toggleState();
  void setCommand(std::string newCommand);
  const std::string &getCommand() const;

private:
  uint8_t currentState = 0;
  std::string command;
};
