all:
	gcc -c *.c database/*.c -Wall
	gcc -o cvet.out *.o
	./cvet.out
clean:
	rm -rf cvet.out *.o
run:
	./cvet.out