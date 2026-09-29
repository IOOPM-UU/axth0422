BUILD ?= debug
BASE_FLAGS=-Wall -Wextra -pedantic --coverage

ifeq ($(BUILD), release)
    FLAGS=$(BASE_FLAGS) -O3 -DNDEBUG
else
    FLAGS=$(BASE_FLAGS) -O0 -g
endif

CC=gcc
OBJECTS=hash_table.o linked_list.o
GCDA_OBJECTS=hash_table.gcda linked_list.gcda

all:
	@echo "Not implemented"

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

%.test.out: $(OBJECTS) %.o
	$(CC) $(FLAGS) $^ -lcunit -o $@

%.out: $(OBJECTS) %.o
	$(CC) $(FLAGS) $^ -o $@

test: tests.test.out
	valgrind --leak-check=full ./tests.test.out
	gcov $(GCDA_OBJECTS)
	gcovr

clean:
	@echo "Not implemented"

.PHONY: test