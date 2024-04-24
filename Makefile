EXEC = ICP
CXX = clang++
CXXFLAGS=-Wall -std=c++17 -g 

HFILES = $(wildcard *.h)
SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

PRO = $(wildcard src/*.pro)
BUILD = build

.PHONY: all clean run pack

all: 
	cd $(BUILD) && qmake ../$(PRO) && make

clean:
	cd $(BUILD) && rm -rf * .[!.]*

run: all
	./$(BUILD)/$(EXEC)

pack: clean
	echo "not implemnted yet"
