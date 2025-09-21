INCLUDE := -I ~/include 
LDFLAGS := -L ~/lib -lsense -lm
all: scroll
scroll: main.o display.o input.o 
		cc -o scroll main.o display.o input.o $(LDFLAGS)
main.o: main.c scroll.h 
	cc -c main.c -I ~/include 
display.o: display.c scroll.h
	cc -c display.c -I ~/include 
input.o: input.c 
	cc -c input.c -I ~/include
run: 
	./scroll
clean: 
	rm -f *.o scroll
