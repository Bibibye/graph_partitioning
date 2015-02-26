PREFIX=.
INCLUDE_DIR=$(PREFIX)/include
SRC_DIR=$(PREFIX)/src

CC=gcc
CFLAGS= -c -std=c99 -g -Wall -Werror
CPPFLAGS= -I$(INCLUDE_DIR) -D_GNU_SOURCE
LDFLAGS=

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRC:%.c=%.o)

OUT=a.out

all: $(OUT)

a.out: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ $(CFLAGS) $(CPPFLAGS) $^

clean:
	$(RM) $(OBJS)
	find -name "*~" -delete

mrproper: clean
	$(RM) $(OUT)
