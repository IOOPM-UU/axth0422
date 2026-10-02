#pragma once

/**
 * @file linked_list.h
 * @author Axel Thornberg & Isaac Pettersson
 * @date 2026-09-24
 * @brief Iterator to operate on linked lists
 * 
 * Linked list iterators provide an interface to iterate through all entries in a linked list.
 * An iterator is either positioned at an entry, called the current entry, or it is positioned at-the-end, if it has already iterated through all entries.
 * If the underlying linked list of an iterator is modified using any non-iterator function, the iterator is invalidated and should not be used anymore.
 * 
 */

#include <stdbool.h>
#include "linked_list.h"
#include "common.h"

typedef struct list_iterator ioopm_list_iterator_t;

/// @brief Create a new iterator
/// @param l the list to iterate over
ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l);

/// @brief Destroy the iterator and return its memory
/// @param iter the iterator
void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter);

/// @brief Checks if there are more elements to iterate over
/// @param iter the iterator
/// @return true if there is at least one more element
bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter);

/// @brief Step the iterator forward one step
/// @param iter the iterator
void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter);

/// @brief Return the current element from the underlying list
/// @param iter the iterator
/// @return the current element
elem_t ioopm_list_iterator_current(ioopm_list_iterator_t *iter);

/// @brief Remove the current element from the underlying list
/// @param iter the iterator
/// @return the removed element
elem_t ioopm_list_iterator_remove(ioopm_list_iterator_t *iter);

/// @brief Insert a new element into the underlying list making the current element it's next
/// @param iter the iterator
/// @param element the element to be inserted
void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, elem_t element);
