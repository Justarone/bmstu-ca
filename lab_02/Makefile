CC = gcc
INCLUDE_DIR = include/
BINARIES = $(patsubst src/%.c,bin/%.o, $(wildcard src/*.c)) \
		   $(patsubst %.c,bin/%.o, $(wildcard *.c))
# Remove -g if not in debug mode
COMPILE_FLAGS = -Wall -Werror -pedantic -std=c99 -g

.PHONY: all test clean
all: app.exe

test: app.exe
	test/test.sh

app.exe: $(BINARIES)
	$(CC) -o $@ -I $(INCLUDE_DIR) $(COMPILE_FLAGS) $^

bin/%.o: src/%.c
	mkdir -p bin
	$(CC) -o $@ -I $(INCLUDE_DIR) $(COMPILE_FLAGS) $^ -c

clean:
	rm -rf bin/ app.exe
