BUILD ?= debug
FLAGS = -Wall -Wextra -pedantic

ifeq ($(BUILD), release)
    FLAGS += -O3 -DNDEBUG
else
    FLAGS += -O0 -g
endif

VPATH = src tests lib
CC = gcc

OBJECTS = db.o hash_table.o linked_list.o utils.o
OUT_OBJECTS = $(patsubst %, dist/%, $(OBJECTS))
OUT_BINARIES = $(patsubst %.o, %.out, $(OUT_OBJECTS))

TEST_OBJECTS = db.test.o
OUT_TEST_OBJECTS = $(patsubst %, dist/%, $(TEST_OBJECTS))
OUT_TEST_BINARIES = $(patsubst %.o, %.out, $(OUT_TEST_OBJECTS))

LCUNIT =

all: dist/main.out
	dist/main.out	

dist:
	mkdir -p dist

dist/%.o: %.c | dist
	@echo $@
	$(CC) $(FLAGS) -c $< -o $@

dist/%.out: $(OUT_OBJECTS) dist/%.o
	$(CC) $(FLAGS) $^ $(LCUNIT) -o $@

%.test: FLAGS += --coverage
%.test: LCUNIT += -lcunit
%.test: dist/%.test.out
	valgrind --track-origins=yes --leak-check=full $<
	
	$(eval GCDA = $(patsubst %.test, dist/%.gcda, $@))
	$(eval GCNO = $(patsubst %.test, dist/%.gcno, $@))

	@mkdir -p dist/tmp_coverage
	@cp $(GCNO) $(GCDA) dist/tmp_coverage

	gcov -b $(GCDA)
	rm -f $(patsubst %.test, %.c.gcov, $@)

	gcovr dist/tmp_coverage/

	@rm -rf dist/tmp_coverage/

test:
	make db.test
	
clean:
	rm -rf ./dist/

.SECONDARY: $(OUT_OBJECTS) $(OUT_BINARIES) $(OUT_TEST_OBJECTS) $(OUT_TEST_BINARIES) dist/main.o
.PHONY: all %.test test clean
