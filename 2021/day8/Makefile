.PHONY = all run clean

CC = g++
CFLAGS = -lm

BINS := main.exe
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=%.o)

all: ${BINS} run clean

${BINS}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o $@

run:
	@.\main.exe

clean:
	@rm -rf ${BINS} ${OBJS}
