#include "hash_table.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    entry_t *buckets[17];
};

static size_t string_knr_hash(const char *str)
{
    size_t result = 0;
    while (*str != '\0')
    {
        result = result * 31 + ((unsigned char) *str);
        str++;
    }
    return result;
}

ioopm_hash_table_t *ioopm_hash_table_create(void)
{
    /// Allocate zeroed-out space for a ioopm_hash_table_t = 17 pointers to entry_t's
    return calloc(1, sizeof(ioopm_hash_table_t));
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
    for (int i = 0; i < 17; i++)
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

entry_t *find_previous_entry(ioopm_hash_table_t *ht, char *key)
{
    // find bucket
    size_t bucket = string_knr_hash(key) % 17;

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
    entry_t *previous = find_previous_entry(ht, key);

    if (previous == NULL)
    {
        size_t bucket = string_knr_hash(key) % 17;

        ht->buckets[bucket] = entry_create(key, value, NULL);
    }
    // if the key exists, update the value, otherwise create a new entry
    else if (previous->next != NULL)
    {
        previous->next->value = value;
    }
    else
    {
        previous->next = entry_create(key, value, NULL);
    }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result)
{

    // // look for an entry with the key we want
    // entry_t *current = ht->buckets[bucket];
    // while (current != NULL && strcmp(current->key, key) != 0)
    // {
    //     current = current->next;
    // }

    entry_t *previous = find_previous_entry(ht, key);
    entry_t *current;

    if (previous == NULL)
    {
        size_t bucket = string_knr_hash(key) % 17;
        current = ht->buckets[bucket];
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

    size_t bucket = string_knr_hash(key) % 17;

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

    free(current);

    return result;
}
