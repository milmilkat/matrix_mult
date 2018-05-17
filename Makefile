OUTPUT=main
BIN_PATH=bin
UNAME := $(shell uname)

# when running on MacOS X, it must use gcc-8
ifeq ($(UNAME), Darwin)
	CC=gcc-8
else
	CC=gcc
endif

run: all
	./$(BIN_PATH)/$(OUTPUT) input/matrix_a input/matrix_b output/matrix_c

all: prepare main.o matrix.o util.o genmatrix.o
	$(CC) $(OUTPUT).o matrix.o util.o -fopenmp -o $(BIN_PATH)/$(OUTPUT)

main.o: main.c
	$(CC) -fopenmp -c $(OUTPUT).c

matrix.o: matrix.c
	$(CC) -fopenmp -c matrix.c

genmatrix.o: genmatrix.c
	$(CC) -fopenmp genmatrix.c -o $(BIN_PATH)/genmatrix

util.o: util.c
	$(CC) -c util.c

prepare: clean
	mkdir $(BIN_PATH)

test:
	$(CC) matrix.o matrix_test.c -o $(BIN_PATH)/matrix_test
	./$(BIN_PATH)/matrix_test

clean:
	rm -f *.o $(OUTPUT)
	rm -Rf $(BIN_PATH)
	rm -f output/*
