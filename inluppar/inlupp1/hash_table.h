#pragma once

/**
 * @file hash_table.h
 * @author Axel Thornberg & Isaac Pettersson
 * @date 2026-09-14
 * @brief Simple hash table that maps keys to values.
 * 
 * Provides an interface for hash tables, for storing data mapped to a key.
 * 
 */

#include <stdbool.h>
#include <stddef.h>
#include "common.h"

typedef struct hash_table ioopm_hash_table_t;

/// @brief Create a new hash table
/// @param hash_fn a function that hashes keys
/// @param key_eq_fn a function that compares keys
/// @return a new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @param result pointer to an elem that the found element gets written to
/// @return a boolean indicating whether the key was present in the hash table or not
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key or -1 if it does not exist
elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key);

/// @brief Check if a key is present in the hash table
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return A boolean indicating whether the key was present in the hash table or not
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

/// @brief Checks if the hash table is empty or not
/// @param ht hash table operated upon
/// @return a boolean indicating whether the hash table is empty or not
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief Checks how many elements are in the hash table
/// @param ht hash table operated upon
/// @return the number of elements are in the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);
