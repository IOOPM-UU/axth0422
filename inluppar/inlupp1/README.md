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

# Initial Profiling Results

The files we were given were too small produce any meaningful data. Therefore we created our own (larger) input file. From this we concluded:

- The top three functions were `find_previous_entry`, `string_compare`, and `string_knr_hash`.
- While the top 3 functions are all our own, `string_compare` does very little other than calling `strcmp`.
- The most time consuming functions were all linear in time complexity and frequently used.
- The program was faster than expected.
- Increasing the number of buckets would reduce the time spent traversing entries.


These results were obtained using gprof.

---

> Made by Isaac Pettersson & Axel Thornberg
