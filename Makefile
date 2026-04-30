# CXX = g++
# CXXFLAGS = -std=c++11 -Wall -I.
# LDFLAGS = -lm
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I. -Ilibs/matplotplusplus/install/include
LDFLAGS = -Llibs/matplotplusplus/install/lib -Llibs/matplotplusplus/install/lib/Matplot++
LDLIBS = -lmatplot -lnodesoup -ljpeg -lpng -ltiff -lpthread -lz -lm

# Находим все .cxx файлы в текущей папке
# SRCS = $(wildcard *.cxx)
SRCS = Inter.cxx stb_image_implementation.cxx
OBJS = $(SRCS:.cxx=.o)
TARGET = program

all: $(TARGET)

$(TARGET): $(OBJS)
# 	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)
#   $(CXX) $(OBJS) -o $(LDFLAGS) $(LDLIBS)
	$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

 #.PHONY: all clean