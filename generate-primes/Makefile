.SUFFIXES:

CXX = clang++
CXXFLAGS = -Wextra -Wall -pedantic -std=c++20 -static -O2 #-Og -g # -fsanitize=undefined  -fsanitize=address
HEADERS = $(filter-out $(EXCLUDED), $(wildcard *.hpp))
OBJECTS = $(addsuffix .o, $(basename  $(filter-out $(EXCLUDED) %Test.cpp main.cpp, $(wildcard *.cpp))))
TESTLIBS = -lgtest -lgtest_main -lpthread
TEST_BINARIES = $(basename $(wildcard *[Tt]est.cpp))

.SECONDARY: $(OBJECTS)

all: compile

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

main: main.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o factoring-bench $^

compile: main

%Test: %Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)  $(TESTLIBS)


format:
	clang-format -i *.cpp *.hpp

clean:
	rm -f *Main *Test *.o main

.PHONY: clean

