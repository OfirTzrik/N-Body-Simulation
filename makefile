# Makefile
CC      := gcc
CFLAGS  := -Wall -Wextra -pedantic
LDFLAGS :=
LDLIBS  := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC_DIR := src
BUILD   := build
SRCS    := $(SRC_DIR)/main.c $(SRC_DIR)/funcs.c
OBJS    := $(SRCS:$(SRC_DIR)/%.c=$(BUILD)/%.o)
TARGET  := $(BUILD)/main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

# Object files in build/
$(BUILD)/%.o: $(SRC_DIR)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build/ exists
$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
