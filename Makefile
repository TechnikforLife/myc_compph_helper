SRCDIR := src
dirs := $(wildcard $(SRCDIR)/*)
#dirs := $(foreach dir,$(SRCDIR),$(wildcard $(dir)/*))
cfiles := $(foreach dir,$(dirs),$(wildcard $(dir)/*.c))
-include processor.mak