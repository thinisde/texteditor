#include "state.hpp"

State::State() : currentState(0) {}

void State::toggleState() { currentState = !currentState; }

uint8_t State::getState() const { return currentState; }
