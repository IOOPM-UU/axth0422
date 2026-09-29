#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"
#include "list_iterator.h"
#include "common.h"

typedef struct entry entry_t;

// ---- Structs ---- //

struct entry
{
    elem_t value;
    entry_t *prev;
    entry_t *next;
};

struct list
{
    entry_t *vanguard;   // Sentinel at the start
    entry_t *sternguard; // Sentinel at the end
    int size;
};

struct list_iterator
{
    entry_t *current;
};

// ---- Linked Lists ---- //

/// @brief Allocates and returns a new linked list entry
entry_t *entry_create(elem_t value, entry_t *prev, entry_t *next)
{
    entry_t *entry = calloc(1, sizeof(entry_t));

    entry->value = value;
    entry->prev = prev;
    entry->next = next;

    return entry;
}

ioopm_list_t *ioopm_list_create(void)
{
    ioopm_list_t *list = calloc(1, sizeof(ioopm_list_t));

    list->vanguard = entry_create(int_elem(0xDEADBEEF), NULL, NULL);
    list->sternguard = entry_create(int_elem(0xDEADBEEF), NULL, NULL);

    list->sternguard->prev = list->vanguard;
    list->vanguard->next = list->sternguard;

    list->size = 0;

    return list;
}

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

void ioopm_list_append(ioopm_list_t *list, elem_t value)
{
    assert(list != NULL);

    entry_t *sternguard = list->sternguard;
    entry_t *entry = entry_create(value, sternguard->prev, sternguard);

    entry->prev->next = entry;
    entry->next->prev = entry;

    list->size += 1;
}

void ioopm_list_prepend(ioopm_list_t *list, elem_t value)
{
    assert(list != NULL);

    entry_t *vanguard = list->vanguard;
    entry_t *entry = entry_create(value, vanguard, vanguard->next);

    entry->prev->next = entry;
    entry->next->prev = entry;

    list->size += 1;
}

elem_t ioopm_list_head(ioopm_list_t *list)
{
    assert(list != NULL);
    assert(ioopm_list_size(list) > 0);

    return list->vanguard->next->value;
}

elem_t ioopm_list_last(ioopm_list_t *list)
{
    assert(list != NULL);
    assert(ioopm_list_size(list) > 0);

    return list->sternguard->prev->value;
}

void ioopm_list_insert(ioopm_list_t *list, int index, elem_t value)
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

elem_t ioopm_list_remove(ioopm_list_t *list, int index)
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

    elem_t value = current->value;

    free(current);

    list->size -= 1;

    return value;
}

elem_t ioopm_list_get(ioopm_list_t *list, int index)
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

int ioopm_list_size(ioopm_list_t *list)
{
    assert(list != NULL);

    return list->size;
}

bool ioopm_list_is_empty(ioopm_list_t *list)
{
    assert(list != NULL);

    return ioopm_list_size(list) == 0;
}

// ---- Iterator ---- //

ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l)
{
    assert(l != NULL);

    ioopm_list_iterator_t *it = calloc(1, sizeof(ioopm_list_iterator_t));
    it->current = l->vanguard->next;

    return it;
}

void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter)
{
    assert(iter != NULL);

    free(iter);
}

bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter)
{
    assert(iter != NULL);

    return iter->current->next == NULL;
}

void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter)
{
    assert(iter != NULL);

    iter->current = iter->current->next;
}

elem_t ioopm_list_iterator_current(ioopm_list_iterator_t *iter)
{
    assert(iter != NULL);

    return iter->current->value;
}

elem_t ioopm_list_iterator_remove(ioopm_list_iterator_t *iter)
{
    assert(iter != NULL);

    entry_t *current = iter->current;

    current->prev->next = current->next;
    current->next->prev = current->prev;

    elem_t value = ioopm_list_iterator_current(iter);

    ioopm_list_iterator_advance(iter);

    free(current);

    return value;
}

void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, elem_t element)
{
    assert(iter != NULL);

    entry_t *current = iter->current;

    entry_t *entry = entry_create(element, current->prev, current);

    current->prev->next = entry;
    current->prev = entry;

    iter->current = iter->current->prev;
}
