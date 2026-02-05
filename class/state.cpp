#include "state.hpp"
#include <utility>

State::State() : currentState(0), command("") {}

void State::setState(uint8_t newState) { currentState = newState; }

uint8_t State::getState() const { return currentState; }

void State::setCommand(std::string newCommand) {
  command = std::move(newCommand);
}

const std::string &State::getCommand() const { return command; }
