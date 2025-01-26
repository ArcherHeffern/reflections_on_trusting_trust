CFLAGS=-std=c11 -g -fno-common -Wall -Wno-switch
INC=-I./include/

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

# Default CC to system GCC
CC=gcc

# Main target using default gcc
compiler: INC=
compiler: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Custom GCC target
bad-compiler: CC=../compiler
bad-compiler: $(OBJS)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(LDFLAGS)

# Pattern rule for object files
$(OBJS): %.o : %.c chibicc.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Clean rule
clean:
	rm -rf gcc bad-gcc $(OBJS)
	find * -type f '(' -name '*~' ')' -exec rm {} ';'

.PHONY: clean gcc bad-gcc
