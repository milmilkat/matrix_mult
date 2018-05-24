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

# build all binaries
all: prepare util.o matrix.o ptmatrix.o ommatrix.o genmatrix.o main.o bench.o
	$(CC) -lpthread -fopenmp -o $(BIN_PATH)/$(OUTPUT) pthreads/ptmatrix.o openmp/ommatrix.o matrix.o util.o $(OUTPUT).o
	$(CC) -lpthread -fopenmp -o $(BIN_PATH)/bench pthreads/ptmatrix.o openmp/ommatrix.o matrix.o util.o benchmark/bench.o
	$(CC) genmatrix.c -o $(BIN_PATH)/genmatrix
	$(CC) matrix.o matrix_test.c -o $(BIN_PATH)/matrix_test

# compiling main file
main.o: main.c
	$(CC) -lpthread -fopenmp -c $(OUTPUT).c -o $(OUTPUT).o

# compiling pthreads module for matrix multiplication
ptmatrix.o: pthreads/ptmatrix.c
	$(CC) -c pthreads/ptmatrix.c -o pthreads/ptmatrix.o -lpthread

# compiling openmp module for matrix multiplication
ommatrix.o: openmp/ommatrix.c
	$(CC) -c openmp/ommatrix.c -o openmp/ommatrix.o -fopenmp

# compiling common module for matrix multiplication
matrix.o: matrix.c
	$(CC) -c matrix.c -o matrix.o

# utility functions (such as get_time) which can be used by any other module than main
util.o: util.c
	$(CC) -c util.c

# prepare the environment for project building
prepare: clean
	mkdir $(BIN_PATH)

# task to run benchmark
bench.o: benchmark/bench.c
	$(CC) -lpthread -fopenmp -c benchmark/bench.c -o benchmark/bench.o

# named tasks
bench:
	./$(BIN_PATH)/bench

test:
	./$(BIN_PATH)/matrix_test

# removes all object and binary files
clean:
	find ./ -iname "*.o" | xargs rm -f
	rm -Rf $(BIN_PATH)
	rm -f output/*
