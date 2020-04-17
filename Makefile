all: test

WARNINGS = -Wall
DEBUG = -ggdb -fno-omit-frame-pointer
OPTIMIZE = -O2

test: Makefile test.c
	$(CC) -o $@ $(WARNINGS) $(DEBUG) $(OPTIMIZE) test.c

clean:
	rm -f test

# Builder will call this to install the application before running.
install:
	echo "Installing is not supported"

# Builder uses this target to run your application.
run:
	./test

