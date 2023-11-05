all: quality demo_shuffle

quality: quality.o riffle.o 
	gcc -ansi quality.o riffle.o -o quality

demo_shuffle: riffle.o demo_shuffle.o
	gcc -ansi demo_shuffle.o riffle.o -o demo_shuffle

riffle.o: riffle.h riffle.c
	gcc -ansi -c riffle.c
	
quality.o: quality.c
	gcc -ansi -c quality.c 
	
demo_shuffle.o: demo_shuffle.c
	gcc -ansi -c demo_shuffle.c

clean:
	rm *.o quality demo_shuffle