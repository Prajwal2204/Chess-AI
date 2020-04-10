chess: main.o funcs.o evaluate.o
	gcc -o chess main.o funcs.o evaluate.o

main.o: main.c
	gcc -c -o main.o main.c

evaluate.o: evaluate.c
	gcc -c -o evaluate.o evaluate.c

funcs.o: funcs.c
	gcc -c -o funcs.o funcs.c


