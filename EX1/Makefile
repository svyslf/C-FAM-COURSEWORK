piglatin: pig.o piglatin.o pig_test.o
	gcc -ansi pig.o pig_test.o piglatin.o -o piglatin

piglatin.o: piglatin.c
	gcc -ansi -c piglatin.c

pig.o: pig.h pig.c
	gcc -ansi -c pig.c

pig_test.o: pig_test.c
	gcc -ansi -c pig_test.c

clean:
	rm *./