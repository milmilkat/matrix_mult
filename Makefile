OUTPUT=main
CC=gcc
BIN_PATH=bin

run: all
	./$(BIN_PATH)/$(OUTPUT) input/matrix_a input/matrix_b output/matrix_c

all: prepare main.o matrix.o
	$(CC) $(OUTPUT).o matrix.o -o $(BIN_PATH)/$(OUTPUT)

main.o: main.c
	$(CC) -c $(OUTPUT).c

matrix.o: matrix.c
	$(CC) -c matrix.c

prepare: clean
	mkdir $(BIN_PATH)

clean:
	rm -f *.o $(OUTPUT)
	rm -Rf $(BIN_PATH)
