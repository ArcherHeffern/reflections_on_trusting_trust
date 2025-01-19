CFLAGS=-std=c11 -g -fno-common -Wall -Wno-switch

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

# Stage 1

gcc: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJS): chibicc.h

# Misc.

clean:
	rm -rf gcc chibicc tmp* 
	find * -type f '(' -name '*~' -o -name '*.o' ')' -exec rm {} ';'

.PHONY: clean 
