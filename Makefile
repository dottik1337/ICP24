EXEC = icp
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

run:
	all && $(build)/$(EXEC)

pack:
	zip -r xgallo06.zip src README.md CHANGELOG.md LICENSE Makefile doc test.py
