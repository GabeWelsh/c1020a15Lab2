all: program

program: main node list stock date
	gcc main.c node.c list.c stock.c date.c -o executable

main: main.c list.h date.h node.h stock.h
	gcc -c main.c

node: node.c node.h
	gcc -c node.c

list: list.c list.h
	gcc -c list.c

stock: stock.c stock.h
	gcc -c stock.c

date: date.c date.h
	gcc -c date.c

clean:
	rm -rf *.gch *.o executable
