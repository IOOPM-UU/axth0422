# Inlupp 1

## Compiling the program

In the terminal run `make all`

## Running the tests

In the terminal run `make test`

## Running the frequency counter

1. Compile the program
1. In the terminal run `./freq_count.out <Paths to each file>`

## Design decisions

- Hash table size is stored in the hash table struct
- Hash tables buckets are a single-linked list without sentinels
- Linked lists are double-linked with sentinels on both ends
- For hash tables, `find_previous_entry` is also used to find the current entry
- Errors are handled by asserts

---

> Made by Isaac Pettersson & Axel Thornberg
