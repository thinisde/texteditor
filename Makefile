CXX      := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
TARGET   := app

SRC := index.cpp \
       class/state.cpp \
       lib/input_handler.cpp \
       lib/input_event_handler.cpp

OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
