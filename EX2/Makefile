riffle: riffle.o demo_shuffle.o
	gcc -ansi demo_shuffle.o riffle.o -o riffle

riffle.o: riffle.h riffle.c
	gcc -ansi -c riffle.c
	
demo_shuffle.o: demo_shuffle.c
	gcc -ansi -c demo_shuffle.c

clean:
	rm *./