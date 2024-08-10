BIN_NAME = neural
BUILD_DIR = build
BIN = $(BUILD_DIR)/$(BIN_NAME)

C_SRC = src/main.c \
	    src/neural.c \
		src/math.c \
		src/matrix.c
OBJS = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(notdir $(C_SRC)))))

CFLAGS = -Wall -Wextra -Werror -std=c99 -O3 -g
CFLAGS += -Iinclude

$(shell mkdir -p $(BUILD_DIR))

all: $(BIN)

$(BUILD_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

run: $(BIN)
	@./$(BIN)

clean:
	rm -rf $(BUILD_DIR)
