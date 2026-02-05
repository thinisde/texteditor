CXX      := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
TARGET   := app

SRC := index.cpp \
       $(wildcard class/*.cpp) \
       $(wildcard lib/*.cpp)

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
