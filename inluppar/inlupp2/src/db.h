#pragma once

/**
 * @file db.h
 * @author Axel Thornberg
 * @date 2026-10-15
 * @brief All backend functionality for the store
 *
 * Provides an interface for the store, providing storage for information about merchandise and where it is physically stored.
 *
 */

#include <stdbool.h>
#include <stddef.h>

typedef struct db ioopm_db_t;

/// @brief Creates the store
/// @return the store
ioopm_db_t *ioopm_create_db();

/// @brief Adds merchandise to the store
/// @param db the store
/// @param name the name of the merchandise
/// @param description a description of the merchandise
/// @param price the price (in SEK) of the merchandise
/// @return whether the operation succeeded or not
bool ioopm_add_merch(ioopm_db_t *db, char *name, char *description, int price);

/// @brief lists the merchandise
/// @param db the store
/// @param output where to write the result
/// @param offset which page of items to display
/// @return whether the operation succeeded or not
bool ioopm_list_merch(ioopm_db_t *db, char *output, int offset);

/// @brief removes merchandise from the store
/// @param db the store
/// @param name the name of the merchandise to remove
/// @return whether the operation succeeded or not
bool ioopm_remove_merch(ioopm_db_t *db, char *name);

/// @brief edits the information of merchandise
/// @param db the store
/// @param old_name the current name of the merch
/// @param new_name the new name of the merch
/// @param new_description the new description of the merch
/// @param new_price the new price of the merch
/// @return whether the operation succeeded or not
bool ioopm_edit_merch(ioopm_db_t *db, char *old_name, char *new_name, char *new_description, int new_price);

/// @brief shows where merchandise is stored
/// @param db the store
/// @param output where to write the result
/// @param product_name the name of the merchandise
/// @return whether the operation succeeded or not
bool ioopm_show_stock(ioopm_db_t *db, char *output, char *product_name);

/// @brief Replenish some merchandise at one shelf
/// @param db the store
/// @param item which item to replenish
/// @param location which shelf to replenish
/// @param amount how much to replenish
/// @return whether the operation succeeded or not
bool ioopm_replenish(ioopm_db_t *db, char *item, char *location, int amount);

/// @brief creates a cart
/// @param db the store
/// @return the id of the cart
size_t ioopm_create_cart(ioopm_db_t *db);

/// @brief deletes a cart
/// @param db the store
/// @param id the id of the cart
/// @return whether the operation succeeded or not
bool ioopm_remove_cart(ioopm_db_t *db, size_t id);

/// @brief adds items to a cart
/// @param db the store
/// @param id the id of the cart
/// @param name the name of the merchandise to add
/// @param amount the amount of merchandise to add
/// @return whether the operation succeeded or not
bool ioopm_add_to_cart(ioopm_db_t *db, size_t id, char *name, int amount);

/// @brief removes items from a cart
/// @param db the store
/// @param id the id of the cart
/// @param name the name of the merchandise to remove
/// @param amount the amount of merchandise to remove
/// @return whether the operation succeeded or not
bool ioopm_remove_from_cart(ioopm_db_t *db, size_t id, char *name, int amount);

/// @brief calculates the cost of all items in a cart
/// @param db the store
/// @param id the id of the cart
/// @param result where to write the result
/// @return whether the operation succeeded or not
bool ioopm_cart_calculate_cost(ioopm_db_t *db, size_t id, int *result);

/// @brief removes the store and frees all memory
/// @param db the store
void ioopm_delete_db(ioopm_db_t *db);

/// @brief checkouts a cart and removes all related items from storage
/// @param db the store
/// @param id the id of the cart
/// @return whether the operation succeeded or not
bool ioopm_checkout(ioopm_db_t *db, size_t id);
