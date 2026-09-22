#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"

typedef struct entry entry_t;

struct entry
{
    int value;
    entry_t *prev;
    entry_t *next;
};

struct list
{
    entry_t *vanguard;   // Sentinel at the start
    entry_t *sternguard; // Sentinel at the end
    int size;
};

entry_t *entry_create(int value, entry_t *prev, entry_t *next)
{
    entry_t *entry = calloc(1, sizeof(entry_t));

    entry->value = value;
    entry->prev = prev;
    entry->next = next;

    return entry;
}

/// @brief Creates a new empty list
/// @return an empty linked list
ioopm_list_t *ioopm_list_create(void)
{
    ioopm_list_t *list = calloc(1, sizeof(ioopm_list_t));

    list->vanguard = entry_create(0xDEADBEEF, NULL, NULL);
    list->sternguard = entry_create(0xDEADBEEF, NULL, NULL);

    list->sternguard->prev = list->vanguard;
    list->vanguard->next = list->sternguard;

    list->size = 0;

    return list;
}

/// @brief Tear down the linked list and return all its memory (but not the memory of the elements)
/// @param list the list to be destroyed
void ioopm_list_destroy(ioopm_list_t *list)
{
    assert(list != NULL);

    int size = ioopm_list_size(list);

    entry_t *current = list->vanguard;
    entry_t *next;

    for (int i = 0; i < size + 2; i++)
    {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

/// @brief Insert at the end of a linked list in O(1) time
/// @param list the linked list that will be appended
/// @param value the value to be appended
void ioopm_list_append(ioopm_list_t *list, int value)
{
    assert(list != NULL);

    entry_t *sternguard = list->sternguard;
    entry_t *entry = entry_create(value, sternguard->prev, sternguard);

    entry->prev->next = entry;
    entry->next->prev = entry;

    list->size += 1;
}

/// @brief Insert at the front of a linked list in O(1) time
/// @param list the linked list that will be prepended to
/// @param value the value to be prepended
void ioopm_list_prepend(ioopm_list_t *list, int value)
{
    assert(list != NULL);

    entry_t *vanguard = list->vanguard;
    entry_t *entry = entry_create(value, vanguard, vanguard->next);

    entry->prev->next = entry;
    entry->next->prev = entry;

    list->size += 1;
}

/// @brief Return the first element of a linked list in O(1) time
/// @pre the list is non-empty
/// @param list the linked list to take the head of
int ioopm_list_head(ioopm_list_t *list)
{
    assert(list != NULL);
    assert(ioopm_list_size(list) > 0);

    return list->vanguard->next->value;
}

/// @brief Return the last element of a linked list in O(1) time
/// @pre the list is non-empty
/// @param list the linked list to take the last element of
int ioopm_list_last(ioopm_list_t *list)
{
    assert(list != NULL);
    assert(ioopm_list_size(list) > 0);

    return list->sternguard->prev->value;
}

/// @brief Insert an element into a linked list in O(n) time.
/// The valid values of index are [0,n] for a list of n elements,
/// where 0 means before the firstelement and n means after
/// the last element.
/// @pre 0 <= index <= length(list)
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @param value the value to be inserted
void ioopm_list_insert(ioopm_list_t *list, int index, int value)
{
    assert(list != NULL);
    assert(index >= 0);
    assert(index <= ioopm_list_size(list));

    int size = ioopm_list_size(list);

    entry_t *entry;

    if (index < size / 2 || size == 0 || (index == size / 2 && size % 2 == 1))
    {
        entry_t *current = list->vanguard->next;

        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        entry = entry_create(value, current->prev, current);
    }
    else
    {
        entry_t *current = list->sternguard->prev;

        for (int i = size; i > index; i--)
        {
            current = current->prev;
        }

        entry = entry_create(value, current, current->next);
    }

    entry->prev->next = entry;
    entry->next->prev = entry;

    list->size += 1;
}

/// @brief Remove an element from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n elements,
/// where 0 means the first element and n-1 means the last element.
/// @pre 0 <= index < length(list)
/// @param list the linked list
/// @param index the position in the list
/// @return the value removed
int ioopm_list_remove(ioopm_list_t *list, int index)
{
    assert(list != NULL);
    assert(index >= 0);
    assert(index < ioopm_list_size(list));

    int size = ioopm_list_size(list);

    entry_t *current;

    if (index < size / 2)
    {
        current = list->vanguard->next;

        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
    }
    else
    {
        current = list->sternguard->prev;

        for (int i = size - 1; i > index; i--)
        {
            current = current->prev;
        }
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;

    int value = current->value;

    free(current);

    list->size -= 1;

    return value;
}

/// @brief Retrieve an element from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n elements,
/// where 0 means the first element and n-1 means the last element.
/// @pre 0 <= index < length(list)
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @return the value at the given position
int ioopm_list_get(ioopm_list_t *list, int index)
{
    assert(list != NULL);
    assert(index >= 0);
    assert(index < ioopm_list_size(list));

    int size = ioopm_list_size(list);

    entry_t *current;

    if (index < size / 2)
    {
        current = list->vanguard->next;

        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
    }
    else
    {
        current = list->sternguard->prev;

        for (int i = size - 1; i > index; i--)
        {
            current = current->prev;
        }
    }

    return current->value;
}

/// @brief Lookup the number of elements in the linked list in O(1) time
/// @param list the linked list
/// @return the number of elements in the list
int ioopm_list_size(ioopm_list_t *list)
{
    assert(list != NULL);

    return list->size;
}

/// @brief Test whether a list is empty or not
/// @param list the linked list
/// @return true if the number of elements int the list is 0, else false
bool ioopm_list_is_empty(ioopm_list_t *list)
{
    assert(list != NULL);

    return ioopm_list_size(list) == 0;
}
