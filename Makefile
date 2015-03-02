PREFIX=.
INCLUDE_DIR=$(PREFIX)/include
SRC_DIR=$(PREFIX)/src

K=2

CC=gcc
CFLAGS= -c -std=c99 -g -Wall -Werror -DK=$(K)
CPPFLAGS= -I$(INCLUDE_DIR) -D_GNU_SOURCE
LDFLAGS=

ifeq ($(DEBUG),yes)
	CFLAGS+= -g -DDEBUG_MODE
else
	CFLAGS+= -O2
endif

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRC:%.c=%.o)

OUT=a.out

.PHONY: clean all mrproper

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
	find -name "*.d" -delete

include $(SRC:.c=.d)

%.d: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -MM $^ > $@
