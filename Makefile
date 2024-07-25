BUILD_DIR = build

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ggdb -std=c99 -fsanitize=undefined
TARGETS = $(BUILD_DIR)/main.o $(BUILD_DIR)/lexer.o $(BUILD_DIR)/interpreter.o $(BUILD_DIR)/compiler.o
SOURCE = src/main.c src/lexer.c src/interpreter.c src/compiler.c

all: $(BUILD_DIR) $(TARGETS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/brainc $(TARGETS)

$(BUILD_DIR):
	mkdir $@

$(BUILD_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(BUILD_DIR)

.PHONY: all clean
