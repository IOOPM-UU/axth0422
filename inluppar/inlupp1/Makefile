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
	make tests.test.out
	make freq_count.out
	rm -f *.gcda *.gcno *.gcov

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
	rm -f *.gcda *.gcno *.out *.o *.gcov

.PRECIOUS: %.o
.PHONY: all test clean