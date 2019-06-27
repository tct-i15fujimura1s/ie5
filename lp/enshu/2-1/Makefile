CC = gcc

.PHONY: all clean
all: calc inf2suf
calc: calc.c
	$(CC) $(CFLAGS) -o $@ $<
inf2suf: inf2suf.c
	$(CC) $(CFLAGS) -o $@ $<
clean:
	rm -f calc inf2suf
