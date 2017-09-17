.POSIX:
.SUFFIXES:

CC := gcc
CFLAGS := -c -std=c99 -pedantic -Wall
LDLIBS := -lGL -lGLU -lGLEW -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lm
RM := rm -f
MKDIR := mkdir -p
NAME := dmatrix

all: obj/ libdmatrix.a $(NAME)

obj/:
	$(MKDIR) obj/

libdmatrix.a: obj/dmatrix.o obj/shader.o
	ar -cvq $@ $^

$(NAME): obj/main.o obj/dmatrix.o obj/shader.o
	$(CC) $^ $(LDLIBS) -o $(NAME)

obj/main.o: src/main.c
	$(CC) $< $(CFLAGS) -o $@

obj/dmatrix.o: src/dmatrix.c src/dmatrix.h
	$(CC) $< $(CFLAGS) -o $@

obj/shader.o: src/shader.c src/shader.h
	$(CC) $< $(CFLAGS) -o $@

.PHONY:
clean:
	$(RM) obj/* $(NAME)
