CC = gcc
CFLAGS = -Wall -Iinc

BIN_DIR = bin
LIB_DIR = lib
SRC_DIR = src
OBJ_DIR = obj

LIB_FILES = $(wildcard $(LIB_DIR)/*.c)
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

LIB_OBJS = $(LIB_FILES:$(LIB_DIR)/%.c=$(OBJ_DIR)/%.o)
SRC_OBJS = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGETS = $(SRC_FILES:$(SRC_DIR)/%.c=$(BIN_DIR)/%)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(LIB_OBJS)
	$(CC) $(OBJ_DIR)/$*.o $(LIB_OBJS) -o $@

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -f $(OBJ_DIR)/* $(BIN_DIR)/*
