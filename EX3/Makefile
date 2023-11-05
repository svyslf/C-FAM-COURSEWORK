all: single byn
single: single.o beggar.o
	gcc -I../EX2 -ansi single.o beggar.o ../EX2/riffle.c -o single 

byn: byn.o beggar.o 
	gcc -I../EX2 -ansi byn.o beggar.o ../EX2/riffle.c -o byn

beggar.o: beggar.h beggar.c
	gcc -ansi -c beggar.c

byn.o: byn.c
	gcc -ansi -c byn.c 

single.o: single.c
	gcc -ansi -c single.c

clean:
	rm *.o single byn