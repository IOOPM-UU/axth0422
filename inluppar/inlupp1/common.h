#pragma once

/**
 * @file common.h
 * @author Axel Thornberg & Isaac Pettersson
 * @date 2026-09-27
 * @brief Types and structs to allow any element to be stored
 */

#include <stdbool.h>
#include <stddef.h>

#define int_elem(x)   ((elem_t) { .i = (x) })
#define bool_elem(x)  ((elem_t) { .b = (x) })
#define ptr_elem(x)   ((elem_t) { .p = (x) })
#define string_elem(x) ((elem_t) { .s = (x) })

typedef union elem elem_t;

typedef bool ioopm_eq_function(elem_t a, elem_t b);

typedef size_t ioopm_hash_function(elem_t key);

/// @brief Allows different types to be stored in one place
union elem
{
  int i;
  unsigned int u;
  bool b;
  float f;
  void *p;
  char *s;
};
