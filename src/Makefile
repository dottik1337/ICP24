EXEC = icp24
CXX = g++
CXXFLAGS=-Wall -std=c++17 -g

HFILES = $(wildcard *.h)
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

clean:
	rm -f $(OBJS) $(EXEC)

doxygen:
	echo "doxygen"

run:
	./icp24