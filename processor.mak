# General settings:
PROFILING := -pg

# Compiler settings:
CC := gcc
CFLAGS = -c
DEBUG := -ggdb
WARNING := -Wall -Wpedantic
OPTIMIZATION := -Og
CFLAGS += $(PROFILING) $(DEBUG) $(WARNING) $(OPTIMIZATION)

# Linker settings:
LDFLAGS =
LIBS := -lm
LDFLAGS += $(PROFILING) $(LIBS)


# Directories:
OBJDIR := obj
BINDIR := bin
SRCDIR := src
DISTDIR := dist

EXECUTIONFILE := test

objects := $(subst $(SRCDIR)/,$(OBJDIR)/,$(cfiles:.c=.o))
deps := $(objects:.o=.d)

.PHONY:	all clean dist cleanall

all: $(BINDIR)/$(EXECUTIONFILE)
-include $(deps)

list-variables:
	@echo cfiles=$(cfiles)
	@echo objects=$(objects)
	@echo deps=$(deps)
	@echo CFLAGS=$(CFLAGS)
	@echo LDFLAGS=$(LDFLAGS)

$(OBJDIR)/%.d : $(SRCDIR)/%.c
	mkdir -p $(@D)
	@echo finding headers of $< ...
	$(CC) -MM -MT "$@ $(patsubst %.d,%.o,$@)" -MF $@ $<

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo compiling $< ...
	$(CC) $(CFLAGS) $< -o $@



$(BINDIR)/$(EXECUTIONFILE) : $(objects) processor.mak Makefile
	@echo linking $@ ...
	mkdir -p $(BINDIR)
	$(CC) -o $@ $(objects) $(LDFLAGS)

$(DISTDIR)/$(EXECUTIONFILE).zip: $(BINDIR)/$(EXECUTIONFILE)
	mkdir -p $(DISTDIR)
	@echo zipping $< ...
	zip -r $(DISTDIR)/$(EXECUTIONFILE).zip $(BINDIR) $(SRCDIR) processor.mak Makefile

dist: $(DISTDIR)/$(EXECUTIONFILE).zip

# Builder will call this to install the application before running.
install:
	echo "Installing is not supported"

# Builder uses this target to run your application.
run:
	$(BINDIR)/$(EXECUTIONFILE)

clean:
	$(RM) -r -f $(OBJDIR)
	$(RM) -r -f $(BINDIR)

cleanall:
	$(RM) -r -f $(OBJDIR)
	$(RM) -r -f $(BINDIR)
	$(RM) -r -f $(DISTDIR)



