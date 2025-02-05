.SUFFIXES:

CXX = clang++
CXXFLAGS = -Wextra -Wall -pedantic -std=c++2b -static -O2 #-Og -g # -fsanitize=undefined  -fsanitize=address
HEADERS = $(filter-out $(EXCLUDED), $(wildcard *.hpp))
OBJECTS = $(addsuffix .o, $(basename  $(filter-out $(EXCLUDED) %Test.cpp main.cpp, $(wildcard *.cpp))))
TESTLIBS = -lgtest -lgtest_main -lpthread
TEST_BINARIES = $(basename $(wildcard *[Tt]est.cpp))

.SECONDARY: $(OBJECTS)

all: compile

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

main: main.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lboost_program_options 

compile: main
	echo "done"

%Test: %Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)  $(TESTLIBS)


format:
	clang-format -i *.cpp *.hpp

clean:
	rm -f *Main *Test *.o

.PHONY: clean

