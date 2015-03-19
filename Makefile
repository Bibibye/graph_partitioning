PREFIX=.
INCLUDE_DIR=$(PREFIX)/include
SRC_DIR=$(PREFIX)/src

K=2

CC=gcc
CFLAGS= -c -std=c99 -g -Wall -Werror -DK=$(K)
CPPFLAGS= -I$(INCLUDE_DIR) -D_GNU_SOURCE
LDFLAGS= -lm

ifeq ($(DEBUG),yes)
	CFLAGS+= -g -DDEBUG_MODE
else
	CFLAGS+= -O2
endif

ifeq ($(RANDOM_ANNEALING),yes)
	CFLAGS+= -DSIMULATED_ANNEALING_RANDOM_ACCEPTATION
endif

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRC:%.c=%.o)

OUT=partition

.PHONY: clean all mrproper

.PRECIOUS: %.d

all: $(OUT)

$(OUT): $(OBJS)
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
