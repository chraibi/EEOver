CC      = g++
CFLAGS  = -Wall -g -fprofile-arcs -ftest-coverage
LDFLAGS = -lgsl -lgslcblas

OBJ = call_ee.o solvers.o zsolve_quartic.o Roots3And4.o

prog: $(OBJ)
	$(CC) $(CFLAGS) -o overlap $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJ)
