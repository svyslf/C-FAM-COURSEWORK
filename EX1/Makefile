all: pig_test piglatin

piglatin: pig.o piglatin.o
	gcc -ansi pig.o piglatin.o -o piglatin

pig_test: pig_test.o pig.o
	gcc -ansi pig.o pig_test.o -o pig_test

piglatin.o: piglatin.c
	gcc -ansi -c piglatin.c

pig.o: pig.h pig.c
	gcc -ansi -c pig.c

pig_test.o: pig_test.c
	gcc -ansi -c pig_test.c

clean:
	rm *.o piglatin pig_test