LIB = src/pnm.c
PROGRAMS = inout wavg1 wavg2 wavg3 median edge1 edge2 edge3 sharpen
IMAGES = $(foreach pgm,$(PROGRAMS),$(pgm).pgm)

.PHONY: all
all: $(PROGRAMS)

$(PROGRAMS): %: src/%.c
	$(CC) -o $@ $< $(LIB)

.PHONY: run
run: $(IMAGES)

$(IMAGES): %.pgm: % res/in.pnm
	./$< res/in.pnm $@

.PHONY: clean
clean:
	rm -f $(PROGRAMS)
	rm -f $(IMAGES)
