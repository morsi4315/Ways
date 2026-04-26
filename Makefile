CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.
LDFLAGS = -lm

# Находим все .cxx файлы в текущей папке
SRCS = $(wildcard *.cxx)
OBJS = $(SRCS:.cxx=.o)
TARGET = program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean