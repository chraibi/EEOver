CC      = g++
CFLAGS  = -Wall -g --coverage
LDFLAGS = -lgsl -lgslcblas --coverage

OBJ = call_ee.o solvers.o zsolve_quartic.o Roots3And4.o

prog: $(OBJ)
	$(CC) $(CFLAGS) -o overlap $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJ)
gcov:
	gcovr -r . --html -o coverage.html --html-details
