CXX = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CXXFLAGS = -g -std=c++11 -Wall -Werror=return-type  -Werror=uninitialized

CATCH = test/catch/catch.o
OBJECTS = cell.o board.o text-menu-app.o

TESTS = test-1-cell test-2-board test-3-gameplay test-4-app

main: $(OBJECTS) main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf *.dSYM test/*.dSYM
	$(RM) *.o *.gc* main test/*.o $(CATCH) $(TESTS)

test-all: $(TESTS)

test-1-cell: cell.o test/test-1-cell.cpp
test-2-board: cell.o board.o test/test-2-board.cpp
test-3-gameplay: cell.o board.o test/test-3-gameplay.cpp
test-4-app: cell.o board.o text-menu-app.o test/test-4-app.cpp

$(TESTS): $(CATCH)
	$(CXX) $(CXXFLAGS) -o $@ $^
	./$@

test-run: main
	./main < test/winner.txt
	@printf -- "\n----------------------------------------------------------\n"
	./main < test/loser.txt

test-memory: test-2-board test-4-app
	valgrind --error-exitcode=1 --leak-check=full ./test-2-board
	@printf -- "\n----------------------------------------------------------\n"
	valgrind --error-exitcode=1 --leak-check=full ./test-4-app
