FLAGS = -O3 -Wall -std=c11
LIBS = -lm

all: utils.o label_handler.o main.o assembler.o data_memory_handler.o
	gcc -g utils.o label_handler.o data_memory_handler.o main.o assembler.o -o assembler $(LIBS)

clean:
	rm -rf *.o assembler

assembler.o: defines.h assembler.c assembler.h
	gcc -g 	$(FLAGS) -c assembler.c

label_handler.o: defines.h label_handler.c label_handler.h
	gcc -g 	$(FLAGS) -c label_handler.c

data_memory_handler.o: defines.h data_memory_handler.c data_memory_handler.h
	gcc -g 	$(FLAGS) -c data_memory_handler.c

utils.o: defines.h utils.c utils.h
	gcc -g $(FLAGS) -c utils.c

main.o: defines.h main.c
	gcc -g $(FLAGS) -c main.c