CC := gcc

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXE := $(BIN_DIR)/main
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS := -Wall -g
LDLIBS := -lm

.PHONY := clean all

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

example: example.o | $(BIN_DIR) $(BIN_DIR)/example
	$(CC) $(OBJ_DIR)/example/example.o -o $(BIN_DIR)/example/$@

example.o: $(SRC_DIR)/example/example.c | $(OBJ_DIR) $(OBJ_DIR)/example
	$(CC) -c $(SRC_DIR)/example/example.c -o $(OBJ_DIR)/example/example.o

$(BIN_DIR)/example $(OBJ_DIR)/example:
	mkdir -p $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)