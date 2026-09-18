# Makefile for Diagrams

TARGET  := diagrams
BUILD   := build

CC      := gcc
CSTD    := -std=c11
WARN    := -Wall -Wextra
CPPFLAGS += -I.
CFLAGS  += $(CSTD) $(WARN) -MMD -MP
LDLIBS  += -lm

# Optimised by default; `make BUILD_TYPE=debug` for an unoptimised build with
# debug info. `make SANITIZE=1` adds ASan/UBSan (needs libasan/libubsan installed).
BUILD_TYPE ?= release
ifeq ($(BUILD_TYPE),debug)
  CFLAGS  += -g3 -O0
else
  CFLAGS  += -O2
endif

ifdef SANITIZE
  CFLAGS  += -fsanitize=address,undefined -fno-omit-frame-pointer
  LDFLAGS += -fsanitize=address,undefined
endif

SRCS := $(wildcard *.c)
OBJS := $(SRCS:%.c=$(BUILD)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD) $(TARGET)

-include $(DEPS)
