CC = gcc --std=gnu99 -g -Wall
exe_file = movies
$(exe_file):  main.o
	$(CC) main.o -o $(exe_file)

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o $(exe_file)

tar:
	tar -cvf $(exe_file).tar *.c *.h bft.txt Makefile