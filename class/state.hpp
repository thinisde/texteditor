#pragma once
#include <cstdint>

class State {
public:
  State();
  uint8_t getState() const;
  void toggleState();

private:
  uint8_t currentState = 0;
};
