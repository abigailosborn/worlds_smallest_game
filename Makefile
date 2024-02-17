S = src/
I = include/
B = build/
OBJ_FILES = $(B)teeny.o
FLAGS = -I$(I) -Iraylib-5.0_linux_amd64/include -Lraylib-5.0_linux_amd64/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: $(B)teeny 

$(B)teeny: $(B)teeny.o
	gcc $< $(FLAGS) -o $@

$(B)teeny.o: $(S)teeny.c
	gcc -c $< $(FLAGS) -o $@

clean:
	rm -rf build
