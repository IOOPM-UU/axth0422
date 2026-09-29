BUILD ?= debug
BASE_FLAGS=-Wall -Wextra -pedantic

ifeq ($(BUILD), release)
    FLAGS=$(BASE_FLAGS) -O3 -DNDEBUG
else
    FLAGS=$(BASE_FLAGS) -O0 -g
endif

CC=gcc
OBJECTS=hash_table.o linked_list.o
COV_FLAGS = $(FLAGS) --coverage

all:
	@echo "Not implemented"

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

%: $(OBJECTS) %.c
	$(CC) $(FLAGS) $^ -o $@

%_tests: $(OBJECTS) %_tests.c
	$(CC) $(COV_FLAGS) $^ -lcunit -o $@	

test:
	@echo "Not implemented"

clean:
	@echo "Not implemented"

.PHONY: test