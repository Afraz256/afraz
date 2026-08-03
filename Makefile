# Build the Course Management System.
#
#   make        build ./cms
#   make clean  remove the binary
#
# -std=c++11 is pinned on purpose. Without it the compiler picks its own
# default, which differs between machines, and warnings that show up on one
# stay invisible on another.

CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wconversion -Wsign-conversion -Wshadow -Wpedantic
TARGET   = cms
SRCS     = $(wildcard *.cpp)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
