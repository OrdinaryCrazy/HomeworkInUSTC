all: \
main.i main.s main.o main \
main_32.i main_32.s main_32.o main_32 \
main_64.i main_64.s main_64.o main_64
.PHONY:all
main: main.c
	gcc -o main main.c 
	
main.o: main.c
	gcc -c main.c
	
main.s: main.c
	gcc -S main.c
	
main.i: main.c
	gcc -E main.c > main.i
	
main_32: main.c
	gcc -m32 -o main_32 main.c 
	
main_32.o: main.c
	gcc -m32 -c main.c
	
main_32.s: main.c
	gcc -m32 -S -o main_32.s main.c
	
main_32.i: main.c
	gcc -m32 -E main.c > main_32.i

main_64: main.c
	gcc -m64 -o main_64 main.c 
	
main_64.o: main.c
	gcc -m64 -c main.c
	
main_64.s: main.c
	gcc -m64 -S -o main_64.s main.c
	
main_64.i: main.c
	gcc -m64 -E main.c > main_64.i
