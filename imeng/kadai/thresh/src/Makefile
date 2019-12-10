LIBS = pnm.c

.PHONY: clean

clean:
	rm $(PROGRAMS)

%: %.c $(LIBS)
	$(CC) -o $@ $< $(LIBS)
