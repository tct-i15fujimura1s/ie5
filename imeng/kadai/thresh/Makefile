PROGRAMS = simple mode discri
RESRCS = cup.pgm source.pgm town.pgm

.PHONY: run all clean $(PROGRAMS)

run: all $(PROGRAMS)
	$(foreach prog,$(PROGRAMS),$(foreach res,$(RESRCS),src/$(prog) res/$(res) $(prog)-$(res); ))

all:
	$(MAKE) -C src $(PROGRAMS)

clean:
	$(RM) *.pgm
	$(MAKE) -C src clean
