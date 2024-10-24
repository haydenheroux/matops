CC = gcc
CFLAGS = -Wall -Imatrix -Itest -g

BIN_DIR = bin
OBJ_DIR = obj
$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR))

MAT_DIR = matrix
TEST_DIR = test
PROB_DIR = problems

MAT_SRC = $(wildcard $(MAT_DIR)/*.c)
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
PROB_SRC = $(wildcard $(PROB_DIR)/*.c)

MAT_OBJ = $(patsubst $(MAT_DIR)/%.c,$(OBJ_DIR)/%.o,$(MAT_SRC))
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRC))
PROB_OBJ = $(patsubst $(PROB_DIR)/%.c,$(OBJ_DIR)/%.o,$(PROB_SRC))

PROBLEMS = $(patsubst $(PROB_DIR)/%.c,$(BIN_DIR)/%,$(PROB_SRC))

all: $(PROBLEMS)

$(BIN_DIR)/%: $(MAT_OBJ) $(TEST_OBJ) $(PROB_OBJ)
	$(CC) $(CFLAGS) -o $@ $(MAT_OBJ) $(TEST_OBJ) $(PROB_OBJ)

$(OBJ_DIR)/%.o: $(MAT_DIR)/%.c $(MAT_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c $(TEST_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PROB_DIR)/%.c $(MAT_DIR)/vector.h $(TEST_DIR)/test.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/* $(BIN_DIR)/*

.PHONY: all clean
