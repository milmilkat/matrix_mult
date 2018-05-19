OUTPUT=main
BIN_PATH=bin
UNAME := $(shell uname)

# when running on MacOS X, it must use gcc-8
ifeq ($(UNAME), Darwin)
	CC=gcc-8
else
	CC=gcc
endif

# just execute the project using some sample data after building the project
run: all
	./$(BIN_PATH)/$(OUTPUT) input/matrix_a input/matrix_b output/matrix_c

# build the result main project
all: prepare util.o matrix.o ptmatrix.o genmatrix.o main.o
	$(CC) -lpthread -fopenmp -o $(BIN_PATH)/$(OUTPUT) pthreads/ptmatrix.o matrix.o util.o $(OUTPUT).o

# compiling main file
main.o: main.c
	$(CC) -lpthread -fopenmp -c $(OUTPUT).c -o $(OUTPUT).o

# compiling pthreads module for matrix multiplication
ptmatrix.o: pthreads/ptmatrix.c
	$(CC) -c pthreads/ptmatrix.c -o pthreads/ptmatrix.o -lpthread

# compiling common module for matrix multiplication
matrix.o: matrix.c
	$(CC) -fopenmp -c matrix.c -o matrix.o

# compiling genmatrix which is allows for matrix generation to a given file
genmatrix.o: genmatrix.c
	$(CC) -fopenmp genmatrix.c -o $(BIN_PATH)/genmatrix

# utility functions (such as get_time) which can be used by any other module than main
util.o: util.c
	$(CC) -c util.c

# prepare the environment for project building
prepare: clean
	mkdir $(BIN_PATH)

# runs unit tests
test:
	$(CC) matrix.o matrix_test.c -o $(BIN_PATH)/matrix_test
	./$(BIN_PATH)/matrix_test

# removes all object and binary files
clean:
	rm -f *.o $(OUTPUT)
	rm -f pthreads/*.o
	rm -Rf $(BIN_PATH)
	rm -f output/*
