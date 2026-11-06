#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"
#include "../lib/common.h"
#include "../lib/hash_table.h"
#include "../lib/hash_table_iterator.h"
#include "../lib/linked_list.h"
#include "../lib/list_iterator.h"

struct db
{
    ioopm_hash_table_t *ht_name_to_item;
    ioopm_hash_table_t *ht_location_to_name;
    ioopm_list_t *carts;
};

struct merch
{
    char *name;
    char *description;
    int price;
    int total_quantity;
    int amount_reserved;
    ioopm_list_t *locs;
};

typedef struct merch merch_t;

struct shelf
{
    char *name;
    int quantity;
};

typedef struct shelf shelf_t;

struct cart_item
{
    char *item;
    int amount;
};

typedef struct cart_item cart_item_t;

struct cart
{
    ioopm_list_t *items;
};

typedef struct cart cart_t;

static bool is_valid_shelf(char *shelf)
{
    if (strlen(shelf) != 3)
    {
        return false;
    }

    char letter = shelf[0];
    char number1 = shelf[1];
    char number2 = shelf[2];

    // The ASCII range with capital letters
    if (letter < 65 || letter > 90)
    {
        return false;
    }

    // The ASCII range with numbers
    if (number1 < 48 || number2 < 48 || number1 > 57 || number2 > 57)
    {
        return false;
    }

    return true;
}

static size_t string_knr_hash(elem_t str)
{
    size_t result = 0;
    while (*str.s != '\0')
    {
        result = result * 31 + ((unsigned char)*str.s);
        str.s++;
    }
    return result;
}

static bool string_compare(elem_t str1, elem_t str2)
{
    return strcmp(str1.s, str2.s) == 0;
}

static int merch_compare(const void *item1, const void *item2)
{
    const merch_t *merch1 = item1;
    const merch_t *merch2 = item2;
    return -strcmp(merch1->name, merch2->name);
}

static int loc_compare(const void *item1, const void *item2)
{
    const shelf_t *shelf1 = item1;
    const shelf_t *shelf2 = item2;
    return strcmp(shelf1->name, shelf2->name);
}

ioopm_db_t *ioopm_create_db()
{
    ioopm_db_t *db = calloc(1, sizeof(ioopm_db_t));
    db->ht_name_to_item = ioopm_hash_table_create(string_knr_hash, string_compare);
    db->ht_location_to_name = ioopm_hash_table_create(string_knr_hash, string_compare);
    db->carts = ioopm_list_create();
    return db;
}

bool ioopm_add_merch(ioopm_db_t *db, char *name, char *description, int price)
{
    if (ioopm_hash_table_has_key(db->ht_name_to_item, string_elem(name)))
    {
        return false;
    }

    merch_t *merch = calloc(1, sizeof(merch_t));
    merch->name = strdup(name);
    merch->description = strdup(description);
    merch->price = price;
    merch->locs = ioopm_list_create();

    ioopm_hash_table_insert(db->ht_name_to_item, string_elem(strdup(name)), ptr_elem(merch));

    return true;
}

bool ioopm_list_merch(ioopm_db_t *db, char *output, int offset)
{
    size_t no_items = ioopm_hash_table_size(db->ht_name_to_item);

    merch_t *items[no_items];

    int item = 0;
    ioopm_hash_table_iterator_t *it;
    for (it = ioopm_hash_table_iterator_create(db->ht_name_to_item); !ioopm_hash_table_iterator_at_end(it); ioopm_hash_table_iterator_advance(it))
    {
        merch_t *merch = ioopm_hash_table_iterator_current_value(it).p;
        items[item] = merch;
        item++;
    }
    ioopm_hash_table_iterator_destroy(it);

    qsort(items, no_items, sizeof(merch_t *), merch_compare);

    size_t start = offset * 20;

    if (start > no_items)
    {
        return false;
    }

    *output = '\0';

    for (size_t i = start; i < start + 20 && i < no_items; i++)
    {
        char merch[255];
        merch_t *item = items[i];
        sprintf(merch, " - %s: %s, %d SEK\n", item->name, item->description, item->price);
        strcat(output, merch);
    }

    return true;
}

bool ioopm_remove_merch(ioopm_db_t *db, char *name)
{
    if (!ioopm_hash_table_has_key(db->ht_name_to_item, string_elem(name)))
    {
        return false;
    }

    char *key = ioopm_hash_table_get_key(db->ht_name_to_item, string_elem(name)).s;

    merch_t *merch = ioopm_hash_table_remove(db->ht_name_to_item, string_elem(name)).p;

    free(key);

    ioopm_list_iterator_t *it;

    for (it = ioopm_list_iterator_create(merch->locs); !ioopm_list_iterator_at_end(it); ioopm_list_iterator_advance(it))
    {
        shelf_t *shelf = ioopm_list_iterator_current(it).p;
        char *key = ioopm_hash_table_get_key(db->ht_location_to_name, string_elem(shelf->name)).p;
        char *name = ioopm_hash_table_remove(db->ht_location_to_name, string_elem(shelf->name)).p;
        free(key);
        free(name);
        free(shelf->name);
        free(shelf);
    }

    ioopm_list_iterator_destroy(it);

    ioopm_list_destroy(merch->locs);

    free(merch->name);
    free(merch->description);
    free(merch);

    ioopm_list_iterator_t *cart_it;

    for (cart_it = ioopm_list_iterator_create(db->carts); !ioopm_list_iterator_at_end(cart_it); ioopm_list_iterator_advance(cart_it))
    {
        cart_t *cart = ioopm_list_iterator_current(cart_it).p;

        if (cart == NULL)
        {
            continue;
        }

        ioopm_list_iterator_t *it;

        for (it = ioopm_list_iterator_create(cart->items); !ioopm_list_iterator_at_end(it); ioopm_list_iterator_advance(it))
        {
            cart_item_t *cart_item = ioopm_list_iterator_current(it).p;

            if (strcmp(cart_item->item, name) != 0)
            {
                continue;
            }

            ioopm_list_iterator_remove(it);

            free(cart_item->item);

            free(cart_item);
        }

        ioopm_list_iterator_destroy(it);
    }

    ioopm_list_iterator_destroy(cart_it);

    return true;
}

bool ioopm_edit_merch(ioopm_db_t *db, char *old_name, char *new_name, char *new_description, int new_price)
{
    if (!ioopm_hash_table_has_key(db->ht_name_to_item, string_elem(old_name)) || (ioopm_hash_table_has_key(db->ht_name_to_item, string_elem(new_name)) && strcmp(old_name, new_name) != 0))
    {
        return false;
    }

    char *key = ioopm_hash_table_get_key(db->ht_name_to_item, string_elem(old_name)).s;

    merch_t *merch = ioopm_hash_table_remove(db->ht_name_to_item, string_elem(old_name)).p;

    free(key);

    ioopm_list_iterator_t *it;

    for (it = ioopm_list_iterator_create(merch->locs); !ioopm_list_iterator_at_end(it); ioopm_list_iterator_advance(it))
    {
        shelf_t *shelf = ioopm_list_iterator_current(it).p;
        elem_t elem = ptr_elem(NULL);
        ioopm_hash_table_lookup(db->ht_location_to_name, string_elem(shelf->name), &elem);
        ioopm_hash_table_insert(db->ht_location_to_name, string_elem(shelf->name), string_elem(strdup(new_name)));
        free(elem.p);
    }

    ioopm_list_iterator_destroy(it);

    free(merch->name);
    free(merch->description);

    merch->name = strdup(new_name);
    merch->description = strdup(new_description);
    merch->price = new_price;

    ioopm_hash_table_insert(db->ht_name_to_item, string_elem(strdup(new_name)), ptr_elem(merch));

    if (strcmp(old_name, new_name) == 0)
    {
        return true;
    }

    ioopm_list_iterator_t *cart_it;

    for (cart_it = ioopm_list_iterator_create(db->carts); !ioopm_list_iterator_at_end(cart_it); ioopm_list_iterator_advance(cart_it))
    {
        cart_t *cart = ioopm_list_iterator_current(cart_it).p;

        if (cart == NULL)
        {
            continue;
        }

        ioopm_list_iterator_t *it;

        for (it = ioopm_list_iterator_create(cart->items); !ioopm_list_iterator_at_end(it); ioopm_list_iterator_advance(it))
        {
            cart_item_t *cart_item = ioopm_list_iterator_current(it).p;

            if (strcmp(cart_item->item, old_name) != 0)
            {
                continue;
            }

            ioopm_list_iterator_remove(it);

            free(cart_item->item);

            cart_item->item = strdup(new_name);

            ioopm_list_iterator_advance(it);

            ioopm_list_iterator_insert(it, ptr_elem(cart_item));

            ioopm_list_iterator_revert(it);
        }

        ioopm_list_iterator_destroy(it);
    }

    ioopm_list_iterator_destroy(cart_it);

    return true;
}

bool ioopm_show_stock(ioopm_db_t *db, char *output, char *product_name)
{
    elem_t elem = ptr_elem(NULL);
    if (!ioopm_hash_table_lookup(db->ht_name_to_item, string_elem(product_name), &elem))
    {
        return false;
    }

    merch_t *merch = elem.p;

    size_t no_locs = ioopm_list_size(merch->locs);

    shelf_t *locs[no_locs];

    int index = 0;
    ioopm_list_iterator_t *it;
    for (it = ioopm_list_iterator_create(merch->locs); !ioopm_list_iterator_at_end(it); ioopm_list_iterator_advance(it))
    {
        shelf_t *shelf = ioopm_list_iterator_current(it).p;
        locs[index] = shelf;
        index++;
    }
    ioopm_list_iterator_destroy(it);

    qsort(locs, no_locs, sizeof(merch_t *), loc_compare);

    *output = '\0';

    for (size_t i = 0; i < no_locs; i++)
    {
        char location[255];
        shelf_t *loc = locs[i];
        sprintf(location, " - %s: %d\n", loc->name, loc->quantity);
        strcat(output, location);
    }

    return true;
}

bool ioopm_replenish(ioopm_db_t *db, char *item, char *location, int amount)
{
    if (!is_valid_shelf(location))
    {
        return false;
    }

    elem_t ptr = ptr_elem(NULL);

    if (!ioopm_hash_table_lookup(db->ht_name_to_item, string_elem(item), &ptr))
    {
        return false;
    }

    merch_t *merch = ptr.p;

    merch->total_quantity += amount;

    ioopm_list_iterator_t *it;

    for (it = ioopm_list_iterator_create(merch->locs); !ioopm_list_iterator_at_end(it); ioopm_list_iterator_advance(it))
    {
        shelf_t *shelf = ioopm_list_iterator_current(it).p;
        if (strcmp(shelf->name, location) == 0)
        {
            shelf->quantity += amount;
            ioopm_list_iterator_destroy(it);
            return true;
        }
    }

    ioopm_list_iterator_destroy(it);

    shelf_t *shelf = calloc(1, sizeof(shelf_t));
    shelf->name = strdup(location);
    shelf->quantity = amount;
    ioopm_list_append(merch->locs, ptr_elem(shelf));

    ioopm_hash_table_insert(db->ht_location_to_name, string_elem(strdup(location)), string_elem(strdup(item)));

    return true;
}

size_t ioopm_create_cart(ioopm_db_t *db)
{
    cart_t *cart = calloc(1, sizeof(cart_t));

    cart->items = ioopm_list_create();

    ioopm_list_append(db->carts, ptr_elem(cart));

    return ioopm_list_size(db->carts);
}

bool ioopm_remove_cart(ioopm_db_t *db, size_t id)
{
    id--;

    if (id >= ioopm_list_size(db->carts))
    {
        return false;
    }
    cart_t *cart = ioopm_list_remove(db->carts, id).p;

    ioopm_list_insert(db->carts, id, ptr_elem(NULL));

    if (cart == NULL)
    {
        return false;
    }

    ioopm_list_iterator_t *it;

    for (it = ioopm_list_iterator_create(cart->items); !ioopm_list_iterator_at_end(it); ioopm_list_iterator_advance(it))
    {
        cart_item_t *cart_item = ioopm_list_iterator_current(it).p;

        free(cart_item->item);
        free(cart_item);
    }

    ioopm_list_iterator_destroy(it);

    ioopm_list_destroy(cart->items);

    free(cart);

    return true;
}

bool ioopm_add_to_cart(ioopm_db_t *db, size_t id, char *name, int amount)
{
    id--;

    if (id >= ioopm_list_size(db->carts))
    {
        return false;
    }

    elem_t elem = ptr_elem(NULL);

    bool has_item = ioopm_hash_table_lookup(db->ht_name_to_item, string_elem(name), &elem);

    merch_t *merch = elem.p;

    if (!has_item || (merch->amount_reserved + amount) > merch->total_quantity)
    {
        return false;
    }

    cart_t *cart = ioopm_list_get(db->carts, id).p;

    if (cart == NULL)
    {
        return false;
    }

    merch->amount_reserved += amount;

    ioopm_list_iterator_t *it;

    for (it = ioopm_list_iterator_create(cart->items); !ioopm_list_iterator_at_end(it); ioopm_list_iterator_advance(it))
    {
        cart_item_t *cart_item = ioopm_list_iterator_current(it).p;

        if (strcmp(name, cart_item->item) == 0)
        {
            cart_item->amount += amount;
            ioopm_list_iterator_destroy(it);
            return true;
        }
    }

    ioopm_list_iterator_destroy(it);

    cart_item_t *cart_item = calloc(1, sizeof(cart_item_t));
    cart_item->amount = amount;
    cart_item->item = strdup(name);

    ioopm_list_append(cart->items, ptr_elem(cart_item));

    return true;
}

bool ioopm_remove_from_cart(ioopm_db_t *db, size_t id, char *name, int amount)
{
    id--;

    if (id >= ioopm_list_size(db->carts))
    {
        return false;
    }

    cart_t *cart = ioopm_list_get(db->carts, id).p;

    if (cart == NULL)
    {
        return false;
    }

    elem_t elem = ptr_elem(NULL);

    bool has_item = ioopm_hash_table_lookup(db->ht_name_to_item, string_elem(name), &elem);

    merch_t *merch = elem.p;

    if (!has_item)
    {
        return false;
    }

    ioopm_list_iterator_t *it;

    for (it = ioopm_list_iterator_create(cart->items); !ioopm_list_iterator_at_end(it); ioopm_list_iterator_advance(it))
    {
        cart_item_t *cart_item = ioopm_list_iterator_current(it).p;

        if (strcmp(name, cart_item->item) == 0 && cart_item->amount >= amount)
        {
            cart_item->amount -= amount;
            merch->amount_reserved -= amount;
            ioopm_list_iterator_destroy(it);
            return true;
        }
    }

    ioopm_list_iterator_destroy(it);

    return false;
}

bool ioopm_cart_calculate_cost(ioopm_db_t *db, size_t id, int *result)
{
    id--;

    if (id >= ioopm_list_size(db->carts))
    {
        return false;
    }

    cart_t *cart = ioopm_list_get(db->carts, id).p;

    if (cart == NULL)
    {
        return false;
    }

    ioopm_list_iterator_t *it;

    for (it = ioopm_list_iterator_create(cart->items); !ioopm_list_iterator_at_end(it); ioopm_list_iterator_advance(it))
    {
        cart_item_t *cart_item = ioopm_list_iterator_current(it).p;

        elem_t elem = ptr_elem(NULL);

        ioopm_hash_table_lookup(db->ht_name_to_item, string_elem(cart_item->item), &elem);

        merch_t *merch = elem.p;

        *result += (merch->price * cart_item->amount);
    }

    ioopm_list_iterator_destroy(it);

    return true;
}

void ioopm_delete_db(ioopm_db_t *db)
{
    ioopm_hash_table_iterator_t *it;
    for (it = ioopm_hash_table_iterator_create(db->ht_name_to_item); !ioopm_hash_table_iterator_at_end(it); ioopm_hash_table_iterator_advance(it))
    {
        char *name = ioopm_hash_table_iterator_current_key(it).s;
        merch_t *merch = ioopm_hash_table_iterator_current_value(it).p;

        ioopm_list_iterator_t *it;

        for (it = ioopm_list_iterator_create(merch->locs); !ioopm_list_iterator_at_end(it); ioopm_list_iterator_advance(it))
        {
            shelf_t *shelf = ioopm_list_iterator_current(it).p;
            free(shelf->name);
            free(shelf);
        }

        ioopm_list_iterator_destroy(it);

        ioopm_list_destroy(merch->locs);

        free(merch->name);
        free(merch->description);
        free(merch);
        free(name);
    }
    ioopm_hash_table_iterator_destroy(it);

    ioopm_hash_table_iterator_t *it2;
    for (it2 = ioopm_hash_table_iterator_create(db->ht_location_to_name); !ioopm_hash_table_iterator_at_end(it2); ioopm_hash_table_iterator_advance(it2))
    {
        free(ioopm_hash_table_iterator_current_key(it2).p);
        free(ioopm_hash_table_iterator_current_value(it2).p);
    }

    ioopm_hash_table_iterator_destroy(it2);

    ioopm_hash_table_destroy(db->ht_name_to_item);
    ioopm_hash_table_destroy(db->ht_location_to_name);

    for (size_t i = 1; i <= ioopm_list_size(db->carts); i++)
    {
        ioopm_remove_cart(db, i);
    }

    ioopm_list_destroy(db->carts);

    free(db);
}

bool ioopm_checkout(ioopm_db_t *db, size_t id)
{
    id--;

    if (id >= ioopm_list_size(db->carts))
    {

        return false;
    }

    cart_t *cart = ioopm_list_get(db->carts, id).p;

    if (cart == NULL)
    {
        return false;
    }

    ioopm_list_iterator_t *it;

    for (it = ioopm_list_iterator_create(cart->items); !ioopm_list_iterator_at_end(it); ioopm_list_iterator_advance(it))
    {
        cart_item_t *cart_item = ioopm_list_iterator_current(it).p;

        elem_t elem = ptr_elem(NULL);

        ioopm_hash_table_lookup(db->ht_name_to_item, string_elem(cart_item->item), &elem);

        merch_t *merch = elem.p;

        merch->total_quantity -= cart_item->amount;
        merch->amount_reserved -= cart_item->amount;

        ioopm_list_iterator_t *locs_it;

        for (locs_it = ioopm_list_iterator_create(merch->locs); !ioopm_list_iterator_at_end(locs_it); ioopm_list_iterator_advance(locs_it))
        {
            shelf_t *shelf = ioopm_list_iterator_current(locs_it).p;

            if (cart_item->amount < shelf->quantity)
            {
                shelf->quantity -= cart_item->amount;
                break;
            }

            ioopm_list_iterator_remove(locs_it);
            char *key = ioopm_hash_table_get_key(db->ht_location_to_name, string_elem(shelf->name)).p;
            char *name = ioopm_hash_table_remove(db->ht_location_to_name, string_elem(shelf->name)).p;
            free(key);
            free(name);

            cart_item->amount -= shelf->quantity;

            free(shelf->name);
            free(shelf);

            if (cart_item->amount == 0)
            {
                break;
            }
        }

        ioopm_list_iterator_destroy(locs_it);
    }

    ioopm_list_iterator_destroy(it);

    return ioopm_remove_cart(db, id + 1);
}
