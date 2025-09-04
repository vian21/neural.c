BIN_NAME = neural
BUILD_DIR = build
BIN = $(BUILD_DIR)/$(BIN_NAME)

C_SRC = src/main.c \
	    src/neural.c \
		src/lib.c \
		src/matrix.c
OBJS = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(notdir $(C_SRC)))))

CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c99 -O3 -g
CFLAGS += -Iinclude
LDLIBS = -lm

$(shell mkdir -p $(BUILD_DIR))

all: $(BIN)

$(BUILD_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

run: $(BIN)
	./$(BIN)

format:
	clang-format -i $(C_SRC) include/*.h

clean:
	rm -rf $(BUILD_DIR)
