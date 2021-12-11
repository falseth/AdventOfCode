.PHONY = all run clean

CC = g++
CFLAGS = -lm

SRCS := $(wildcard *.cpp)
BINS := $(SRCS:%.cpp=%.exe)
OBJS := $(SRCS:%.cpp=%.o)

all: ${BINS} run clean

${BINS}: ${OBJS}
	@${CC} ${CFLAGS} $< -o $@

${OBJS}: ${SRCS}
	@${CC} -c $< -o $@

run:
	@.\main.exe

clean:
	@rm -rf ${BINS} ${OBJS}
