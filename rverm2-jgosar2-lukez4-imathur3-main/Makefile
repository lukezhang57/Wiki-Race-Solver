CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++2a -g -Wall -Wextra -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./src/wikipedia.cpp ./src/main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests: ./tests/tests.cpp ./src/wikipedia.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.DEFAULT_GOAL := tests
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
