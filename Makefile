CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude
TARGET   := streaming
SRC      := main.cpp src/Video.cpp src/Pelicula.cpp src/Serie.cpp src/Episodio.cpp

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
