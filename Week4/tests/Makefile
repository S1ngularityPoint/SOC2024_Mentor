CC=g++
# CFLAGS=-Wall
CFLAGS = 

all: Optr Exp MOp Max

Optr: testBasicOperators.cpp
	$(CC) $(CFLAGS) testBasicOperators.cpp ../matrix/naive.cpp -o test_op
	./test_op
Exp: testExp.cpp
	$(CC) $(CFLAGS) testExp.cpp ../matrix/naive.cpp -o test_exp
	./test_exp
MOp: testMatrOps.cpp
	$(CC) $(CFLAGS) testMatrOps.cpp ../matrix/naive.cpp -o test_mop
	./test_mop
Max: testMax.cpp
	$(CC) $(CFLAGS) testMax.cpp ../matrix/naive.cpp -o test_max
	./test_max
clean:
	rm ./test_op ./test_exp ./test_mop ./test_max