LIB = pnm.c
PROGRAM = inout wavg1 wavg2 wavg3 median edge1 edge2

.PHONY: all

all: $(PROGRAM)

inout: $(LIB) inout.c
	$(CC) -o $@ $^

wavg1: $(LIB) wavg1.c
	$(CC) -o $@ $^

wavg2: $(LIB) wavg2.c
	$(CC) -o $@ $^

wavg3: $(LIB) wavg3.c
	$(CC) -o $@ $^

median: $(LIB) median.c
	$(CC) -o $@ $^

edge1: $(LIB) edge1.c
	$(CC) -o $@ $^

edge2: $(LIB) edge2.c
	$(CC) -o $@ $^

.PHONY: clean
clean:
	rm -rf $(PROGRAM)
