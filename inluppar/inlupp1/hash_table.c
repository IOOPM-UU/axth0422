#include "hash_table.h"
#include "hash_table_iterator.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define No_Buckets 17

typedef struct entry entry_t;
struct entry
{
    char *key;     // holds the key
    int value;     // holds the value
    entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
    // DODGE: hard-coding number of buckets as 17.
    // NOTE: addressing this dodge is optional.
    entry_t *buckets[No_Buckets];
    int size;
};

struct hash_table_iterator
{
    ioopm_hash_table_t *ht;
    int current_bucket;
    entry_t *current_entry;
};

// ---- Hash Table ---- //

static size_t string_knr_hash(const char *str)
{
    size_t result = 0;
    while (*str != '\0')
    {
        result = result * 31 + ((unsigned char)*str);
        str++;
    }
    return result;
}

ioopm_hash_table_t *ioopm_hash_table_create(void)
{
    /// Allocate zeroed-out space for a ioopm_hash_table_t = 17 pointers to entry_t's
    ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
    ht->size = 0;
    return ht;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
    for (int i = 0; i < No_Buckets; i++)
    {
        entry_t *previous = NULL;
        entry_t *current = ht->buckets[i]; // The same as *(ht->buckets + i)
        while (current != NULL)
        {
            previous = current;
            current = current->next;
            free(previous->key);
            free(previous);
        }
    }

    free(ht);
}

entry_t *find_current_entry(ioopm_hash_table_t *ht, char *key)
{
    // find bucket
    size_t bucket = string_knr_hash(key) % No_Buckets;

    // look for an entry with the key we want
    entry_t *current = ht->buckets[bucket];

    while (current != NULL && strcmp(current->key, key) != 0)
    {
        current = current->next;
    }

    return current;
}

entry_t *find_previous_entry(ioopm_hash_table_t *ht, char *key)
{
    // find bucket
    size_t bucket = string_knr_hash(key) % No_Buckets;

    // look for an entry with the key we want
    entry_t *previous = NULL;
    entry_t *current = ht->buckets[bucket];
    while (current != NULL && strcmp(current->key, key) != 0)
    {
        previous = current;
        current = current->next;
    }

    return previous;
}

static entry_t *entry_create(char *key, int value, entry_t *next)
{
    entry_t *entry = calloc(1, sizeof(entry_t));
    entry->key = key;
    entry->value = value;
    entry->next = next;
    return entry;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value)
{

    // find previous entry, or the last entry if the key does not exist
    entry_t *current = find_current_entry(ht, key);

    if (current == NULL)
    {
        size_t bucket = string_knr_hash(key) % No_Buckets;

        ht->buckets[bucket] = entry_create(strdup(key), value, ht->buckets[bucket]);

        ht->size += 1;
    }
    else
    {
        current->value = value;
    }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result)
{
    entry_t *previous = find_previous_entry(ht, key);
    entry_t *current;

    if (previous == NULL)
    {
        size_t bucket = string_knr_hash(key) % No_Buckets;
        current = ht->buckets[bucket]; // The same as *(ht->buckets + bucket)
    }
    else
    {
        current = previous->next;
    }

    // if the key exists, return the value, otherwise, indicate that the lookup failed
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

int ioopm_hash_table_remove(ioopm_hash_table_t *ht, char *key)
{
    entry_t *previous = find_previous_entry(ht, key);
    entry_t *current;

    size_t bucket = string_knr_hash(key) % No_Buckets;

    if (ht->buckets[bucket] == NULL)
    {
        return -1;
    }

    if (previous == NULL)
    {
        current = ht->buckets[bucket];
        ht->buckets[bucket] = current->next;
    }
    else
    {
        current = previous->next;
        previous->next = current->next;
    }

    int result = current->value;

    free(current->key);
    free(current);

    ht->size -= 1;

    return result;
}

// TODO: documentation
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, char *key)
{
    size_t bucket = string_knr_hash(key) % No_Buckets;

    entry_t *current = ht->buckets[bucket];

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return true;
        }

        current = current->next;
    }

    return false;
}

// TODO: documentation
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
    return ht->size == 0;
}

// TODO: documentation
int ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
    return ht->size;
}

// ---- Iterator ---- //

ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht)
{
    ioopm_hash_table_iterator_t *it = calloc(1, sizeof(ioopm_hash_table_iterator_t));
    it->ht = ht;

    if (ioopm_hash_table_is_empty(ht))
    {
        it->current_bucket = No_Buckets;
        it->current_entry = ht->buckets[0];
        return it;
    }

    it->current_bucket = 0;

    for (int i = 0; i < No_Buckets && ht->buckets[i] == NULL; i++)
    {
        it->current_bucket = i + 1;
    }

    it->current_entry = ht->buckets[it->current_bucket];

    return it;
}

void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it)
{
    free(it);
}

bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it)
{
    return it->current_bucket == No_Buckets;
}

void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it)
{

    // advance to the next entry in the bucket
    it->current_entry = it->current_entry->next;

    if (it->current_entry != NULL)
    {
        return;
    }

    // if it was null advance to the next bucket
    do
    {
        it->current_bucket += 1;
    } while (it->ht->buckets[it->current_bucket] == NULL && it->current_bucket < No_Buckets);

    // if the next bucket existed, update the current entry
    if (it->current_bucket != No_Buckets)
    {
        it->current_entry = it->ht->buckets[it->current_bucket];
    }
}

char *ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it)
{
    return strdup(it->current_entry->key);
}

int ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it)
{
    return it->current_entry->value;
}
