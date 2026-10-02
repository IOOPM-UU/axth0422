#include "hash_table.h"
#include "hash_table_iterator.h"
#include "common.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define No_Buckets 17

typedef struct entry entry_t;

// ---- Structs ---- //

struct entry
{
    elem_t key;    // holds the key
    elem_t value;  // holds the value
    entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
    entry_t *buckets[No_Buckets];
    ioopm_hash_function *hash_fn;
    ioopm_eq_function *key_eq_fn;
    size_t size;
};

struct hash_table_iterator
{
    ioopm_hash_table_t *ht;
    size_t current_bucket;
    entry_t *current_entry;
};

// ---- Hash Table ---- //

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn)
{
    ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
    ht->size = 0;
    ht->hash_fn = hash_fn;
    ht->key_eq_fn = key_eq_fn;
    return ht;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
    assert(ht != NULL);

    for (size_t i = 0; i < No_Buckets; i++)
    {
        entry_t *previous = NULL;
        entry_t *current = ht->buckets[i];
        while (current != NULL)
        {
            previous = current;
            current = current->next;
            free(previous);
        }
    }

    free(ht);
}

/// @brief Returns a pointer to the previous element or null if the element does not exist
entry_t **find_previous_entry(ioopm_hash_table_t *ht, elem_t key)
{
    size_t bucket = ht->hash_fn(key) % No_Buckets;

    entry_t **prev = &ht->buckets[bucket];

    while ((*prev) != NULL && !ht->key_eq_fn((*prev)->key, key))
    {
        prev = &(*prev)->next;
    }

    return prev;
}

/// @brief Allocates and returns a new hash table entry
static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
    entry_t *entry = calloc(1, sizeof(entry_t));
    entry->key = key;
    entry->value = value;
    entry->next = next;
    return entry;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
    assert(ht != NULL);

    entry_t *current = *find_previous_entry(ht, key);

    if (current == NULL)
    {
        size_t bucket = ht->hash_fn(key) % No_Buckets;

        ht->buckets[bucket] = entry_create(key, value, ht->buckets[bucket]);

        ht->size += 1;
    }
    else
    {
        current->value = value;
    }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result)
{
    assert(ht != NULL);

    entry_t *current = *find_previous_entry(ht, key);

    if (current != NULL)
    {
        *result = current->value;
        return true;
    }
    else
    {
        return false;
    }
}

elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
{
    assert(ht != NULL);

    entry_t **prev = find_previous_entry(ht, key);

    if ((*prev) == NULL)
    {
        return int_elem(-1);
    }

    entry_t *current = (*prev);

    (*prev) = current->next;

    elem_t result = current->value;

    free(current);

    ht->size -= 1;

    return result;
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
    assert(ht != NULL);

    size_t bucket = ht->hash_fn(key) % No_Buckets;

    entry_t *current = ht->buckets[bucket];

    while (current != NULL)
    {
        if (ht->key_eq_fn(current->key, key))
        {
            return true;
        }

        current = current->next;
    }

    return false;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
    assert(ht != NULL);

    return ht->size == 0;
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
    assert(ht != NULL);

    return ht->size;
}

// ---- Iterator ---- //

ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht)
{
    assert(ht != NULL);

    ioopm_hash_table_iterator_t *it = calloc(1, sizeof(ioopm_hash_table_iterator_t));
    it->ht = ht;

    if (ioopm_hash_table_is_empty(ht))
    {
        it->current_bucket = No_Buckets;
        it->current_entry = ht->buckets[0];
        return it;
    }

    it->current_bucket = 0;

    for (size_t i = 0; i < No_Buckets && ht->buckets[i] == NULL; i++)
    {
        it->current_bucket = i + 1;
    }

    it->current_entry = ht->buckets[it->current_bucket];

    return it;
}

void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it)
{
    assert(it != NULL);

    free(it);
}

bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it)
{
    assert(it != NULL);

    return it->current_bucket == No_Buckets;
}

void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it)
{
    assert(it != NULL);

    // advance to the next entry in the bucket
    it->current_entry = it->current_entry->next;

    if (it->current_entry != NULL)
    {
        return;
    }

    do
    {
        it->current_bucket += 1;
    } while (it->ht->buckets[it->current_bucket] == NULL && it->current_bucket < No_Buckets);

    if (it->current_bucket != No_Buckets)
    {
        it->current_entry = it->ht->buckets[it->current_bucket];
    }
}

elem_t ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it)
{
    assert(it != NULL);

    return it->current_entry->key;
}

elem_t ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it)
{
    assert(it != NULL);

    return it->current_entry->value;
}
