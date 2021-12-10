.PHONY = all run clean

CC = g++
CFLAGS = -lm

all: main.exe run clean

main.exe: main.o EasyBMP.o
	@${CC} ${CFLAGS} main.o EasyBMP.o -o $@

main.o: main.cpp
	@${CC} ${CFLAGS} -c $< -o $@

EasyBMP.o: EasyBMP.cpp
	@${CC} ${CFLAGS} -c $< -o $@

run:
	@.\main.exe

clean:
	@rm -rf main.exe main.o EasyBMP.o
