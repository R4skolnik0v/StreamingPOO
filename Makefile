CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

TARGET   := streaming
SRCS     := main.cpp \
            src/Video.cpp \
            src/Pelicula.cpp \
            src/Serie.cpp \
            src/Episodio.cpp \
            src/Catalogo.cpp

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
