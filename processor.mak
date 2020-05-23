# General settings:
PROFILING := -pg

# Compiler settings:
CC := gcc
CFLAGS = -c
DEBUG := -ggdb
WARNING := -Wall -Wpedantic
OPTIMIZATION := -Og
CFLAGS += $(PROFILING) $(DEBUG) $(WARNING) $(OPTIMIZATION)

# Directories:
OBJDIR := obj
BINDIR := bin
SRCDIR := src
DISTDIR := dist
DATADIR := data
PYTHDIR := pyth
GPDIR := gplot

# Linker settings:
LDFLAGS =
LIBS := -lm -lgsl -lblas
LDFLAGS += $(PROFILING) $(LIBS)


EXECUTIONFILE := test

objects := $(subst $(SRCDIR)/,$(OBJDIR)/,$(cfiles:.c=.o))
deps := $(objects:.o=.d)

.PHONY:	all clean dist cleanall

all: $(BINDIR)/$(EXECUTIONFILE)
-include $(deps)

# List all make variables
list-variables:
	@echo cfiles=$(cfiles)
	@echo objects=$(objects)
	@echo deps=$(deps)
	@echo CFLAGS=$(CFLAGS)
	@echo LDFLAGS=$(LDFLAGS)

# generate dependencies
$(OBJDIR)/%.d : $(SRCDIR)/%.c
	mkdir -p $(@D)
	@echo [make] finding headers of $< ...
	$(CC) -MM -MT "$@ $(patsubst %.d,%.o,$@)" -MF $@ $<

# compiling
$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo [make] compiling $< ...
	$(CC) $(CFLAGS) $< -o $@

# linking
$(BINDIR)/$(EXECUTIONFILE) : $(objects) processor.mak Makefile
	@echo [make] linking $@ ...
	mkdir -p $(BINDIR)
	$(CC) -o $@ $(objects) $(LDFLAGS)

#distribute
$(DISTDIR)/$(EXECUTIONFILE).zip: $(BINDIR)/$(EXECUTIONFILE)
	mkdir -p $(DISTDIR)
	@echo [make] zipping $< ...
	zip -r $(DISTDIR)/$(EXECUTIONFILE).zip $(BINDIR) $(SRCDIR) processor.mak Makefile

dist: $(DISTDIR)/$(EXECUTIONFILE).zip

# Builder will call this to install the application before running.
install:
	echo "Installing is not supported"

#plot
plot:
	@echo [make] plotting ...
	gnuplot $(GPDIR)/script.plt
#python3 $(PYTHDIR)/simpleplotter.py

#main calculation
calc:
	$(BINDIR)/$(EXECUTIONFILE)

# Builder uses this target to run the application.
run:
	make calc
	make plot

#clean directrories
clean:
	$(RM) -r -f $(OBJDIR)
	$(RM) -r -f $(BINDIR)

cleanall:
	$(RM) -r -f $(OBJDIR)
	$(RM) -r -f $(BINDIR)
	$(RM) -r -f $(DISTDIR)



