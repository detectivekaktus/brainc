CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ggdb -std=c99 -fsanitize=undefined
TARGETS = build/main.o
SOURCE = src/main.c
BUILD_DIR = build

all: $(BUILD_DIR) $(TARGETS)
	$(CC) $(CFLAGS) -o build/brainc $(TARGETS)

$(BUILD_DIR):
	mkdir $@

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(BUILD_DIR)

.PHONY: all clean
