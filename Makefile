CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c99 -O3 -g
CFLAGS += -Iinclude
LDLIBS = -lm

BUILD_DIR = build

LIB_SRC = src/neural.c \
		src/lib.c \
		src/matrix.c
LIBS = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(notdir $(LIB_SRC)))))

PROG_SRC = src/mnist.c

$(shell mkdir -p $(BUILD_DIR))

$(BUILD_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

mnist: $(BUILD_DIR)/mnist.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$@ $(LDLIBS) 

format:
	clang-format -i src/*.c include/*.h

clean:
	rm -rf $(BUILD_DIR)
