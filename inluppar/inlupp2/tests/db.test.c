#include <CUnit/Basic.h>
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include "../src/db.h"

int init_suite(void)
{
    // Change this function if you want to do something *before* you
    // run a test suite
    return 0;
}

int clean_suite(void)
{
    // Change this function if you want to do something *after* you
    // run a test suite
    return 0;
}

// ---- Tests ---- //

void test_create_destroy_db(void)
{
    ioopm_db_t *db = ioopm_create_db();

    CU_ASSERT_PTR_NOT_NULL(db);

    ioopm_delete_db(db);
}

void test_add_merch(void)
{
    ioopm_db_t *db = ioopm_create_db();

    CU_ASSERT_TRUE(ioopm_add_merch(db, "Item1", "Desc1", 100));
    CU_ASSERT_TRUE(ioopm_add_merch(db, "Item2", "Desc2", 10));
    CU_ASSERT_FALSE(ioopm_add_merch(db, "Item1", "Desc3", 50));

    char result[255 * 20] = "";
    CU_ASSERT_TRUE(ioopm_list_merch(db, result, 0));
    CU_ASSERT_STRING_EQUAL(result, " - Item1: Desc1, 100 SEK\n - Item2: Desc2, 10 SEK\n");

    ioopm_delete_db(db);
}

void test_replenish_stock(void)
{
    ioopm_db_t *db = ioopm_create_db();

    CU_ASSERT_TRUE(ioopm_add_merch(db, "Item1", "Desc1", 100));

    CU_ASSERT_TRUE(ioopm_replenish(db, "Item1", "A10", 20));
    CU_ASSERT_TRUE(ioopm_replenish(db, "Item1", "B50", 10));
    CU_ASSERT_TRUE(ioopm_replenish(db, "Item1", "B50", 10));

    char result[255 * 20] = "";
    CU_ASSERT_TRUE(ioopm_show_stock(db, result, "Item1"));
    CU_ASSERT_STRING_EQUAL(result, " - A10: 20\n - B50: 20\n");

    ioopm_delete_db(db);
}

void test_remove_merch(void)
{
    ioopm_db_t *db = ioopm_create_db();

    CU_ASSERT_TRUE(ioopm_add_merch(db, "Item1", "Desc1", 100));

    CU_ASSERT_TRUE(ioopm_remove_merch(db, "Item1"));
    CU_ASSERT_FALSE(ioopm_remove_merch(db, "Item2"));

    char result[255 * 20] = "";
    CU_ASSERT_TRUE(ioopm_list_merch(db, result, 0));
    CU_ASSERT_STRING_EQUAL(result, "");

    CU_ASSERT_FALSE(ioopm_list_merch(db, result, 1));

    ioopm_delete_db(db);
}

void test_edit_merch(void)
{
    ioopm_db_t *db = ioopm_create_db();

    CU_ASSERT_TRUE(ioopm_add_merch(db, "Item1", "Desc1", 100));
    CU_ASSERT_TRUE(ioopm_add_merch(db, "Item2", "Desc2", 100));

    CU_ASSERT_TRUE(ioopm_replenish(db, "Item1", "A10", 50));

    CU_ASSERT_TRUE(ioopm_edit_merch(db, "Item1", "Thing1", "Summary1", 500));
    CU_ASSERT_FALSE(ioopm_edit_merch(db, "Item1", "Thing2", "Summary2", 500));
    CU_ASSERT_FALSE(ioopm_edit_merch(db, "Item2", "Thing1", "Summary3", 500));

    char result[255 * 20] = "";
    CU_ASSERT_TRUE(ioopm_list_merch(db, result, 0));
    CU_ASSERT_STRING_EQUAL(result, " - Item2: Desc2, 100 SEK\n - Thing1: Summary1, 500 SEK\n");

    ioopm_delete_db(db);
}

void test_create_destroy_cart(void)
{
    ioopm_db_t *db = ioopm_create_db();

    int id = ioopm_create_cart(db);

    CU_ASSERT_EQUAL(id, 1);

    CU_ASSERT_TRUE(ioopm_remove_cart(db, id));

    ioopm_delete_db(db);
}

void test_add_to_cart(void)
{
    ioopm_db_t *db = ioopm_create_db();

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0001", "0001", 1));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0001", "A01", 1));

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0002", "0002", 2));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0002", "A02", 2));

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0003", "0003", 3));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0003", "A03", 3));

    int id = ioopm_create_cart(db);

    CU_ASSERT_TRUE(ioopm_add_to_cart(db, id, "0002", 1));
    CU_ASSERT_TRUE(ioopm_add_to_cart(db, id, "0002", 1));
    CU_ASSERT_TRUE(ioopm_add_to_cart(db, id, "0003", 2));

    int result = 0;
    CU_ASSERT_TRUE(ioopm_cart_calculate_cost(db, id, &result));
    CU_ASSERT_EQUAL(result, 10);

    CU_ASSERT_FALSE(ioopm_add_to_cart(db, id, "0001", 2));

    CU_ASSERT_TRUE(ioopm_remove_cart(db, id));

    ioopm_delete_db(db);
}

void test_remove_from_cart(void)
{
    int result;

    ioopm_db_t *db = ioopm_create_db();

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0001", "0001", 1));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0001", "A01", 1));

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0002", "0002", 2));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0002", "A02", 2));

    int id = ioopm_create_cart(db);

    CU_ASSERT_TRUE(ioopm_add_to_cart(db, id, "0002", 2));

    result = 0;
    CU_ASSERT_TRUE(ioopm_cart_calculate_cost(db, id, &result));
    CU_ASSERT_EQUAL(result, 4);

    CU_ASSERT_TRUE(ioopm_remove_from_cart(db, id, "0002", 1));

    result = 0;
    CU_ASSERT_TRUE(ioopm_cart_calculate_cost(db, id, &result));
    CU_ASSERT_EQUAL(result, 2);

    CU_ASSERT_TRUE(ioopm_remove_from_cart(db, id, "0002", 1));

    result = 0;
    CU_ASSERT_TRUE(ioopm_cart_calculate_cost(db, id, &result));
    CU_ASSERT_EQUAL(result, 0);

    CU_ASSERT_FALSE(ioopm_remove_from_cart(db, id, "0004", 4));

    CU_ASSERT_TRUE(ioopm_remove_cart(db, id));

    ioopm_delete_db(db);
}

void test_checkout(void)
{
    ioopm_db_t *db = ioopm_create_db();

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0001", "0001", 1));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0001", "A01", 1));

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0002", "0002", 2));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0002", "A02", 2));

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0003", "0003", 3));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0003", "A03", 3));

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0004", "0004", 4));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0004", "A04", 4));

    int id = ioopm_create_cart(db);

    CU_ASSERT_TRUE(ioopm_add_to_cart(db, id, "0001", 1));
    CU_ASSERT_TRUE(ioopm_add_to_cart(db, id, "0002", 2));
    CU_ASSERT_TRUE(ioopm_add_to_cart(db, id, "0003", 2));
    CU_ASSERT_TRUE(ioopm_add_to_cart(db, id, "0004", 4));

    CU_ASSERT_TRUE(ioopm_replenish(db, "0004", "C99", 1));

    CU_ASSERT_TRUE(ioopm_checkout(db, id));

    ioopm_delete_db(db);
}

void test_invalid_shelf(void)
{
    ioopm_db_t *db = ioopm_create_db();

    CU_ASSERT_FALSE(ioopm_replenish(db, "Item1", "A100", 10));
    CU_ASSERT_FALSE(ioopm_replenish(db, "Item1", "(10", 20));
    CU_ASSERT_FALSE(ioopm_replenish(db, "Item1", "ABB", 30));

    ioopm_delete_db(db);
}

void test_stock_item_does_not_exist(void)
{
    ioopm_db_t *db = ioopm_create_db();

    char result[255 * 20] = "";
    CU_ASSERT_FALSE(ioopm_show_stock(db, result, "Item1"));

    ioopm_delete_db(db);
}

void test_replenish_item_does_not_exist(void)
{
    ioopm_db_t *db = ioopm_create_db();

    CU_ASSERT_FALSE(ioopm_replenish(db, "Item", "A10", 100));

    ioopm_delete_db(db);
}

void test_edit_cart_does_not_exist(void)
{
    ioopm_db_t *db = ioopm_create_db();

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0001", "0001", 1));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0001", "A01", 1));

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0002", "0002", 2));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0002", "A02", 2));

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0003", "0003", 3));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0003", "A03", 3));

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0004", "0004", 4));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0004", "A04", 4));

    int id = ioopm_create_cart(db);

    int result = -1;

    CU_ASSERT_FALSE(ioopm_add_to_cart(db, id + 1, "0001", 1));
    CU_ASSERT_FALSE(ioopm_remove_from_cart(db, id + 1, "0001", 1));
    CU_ASSERT_FALSE(ioopm_cart_calculate_cost(db, id + 1, &result));
    CU_ASSERT_FALSE(ioopm_checkout(db, id + 1));
    CU_ASSERT_FALSE(ioopm_remove_cart(db, id + 1));

    CU_ASSERT_TRUE(ioopm_remove_cart(db, id));

    CU_ASSERT_FALSE(ioopm_add_to_cart(db, id, "0001", 1));
    CU_ASSERT_FALSE(ioopm_remove_from_cart(db, id, "0001", 1));
    CU_ASSERT_FALSE(ioopm_cart_calculate_cost(db, id, &result));
    CU_ASSERT_FALSE(ioopm_checkout(db, id));
    CU_ASSERT_FALSE(ioopm_remove_cart(db, id));

    ioopm_delete_db(db);
}

void test_remove_item_before_checkout(void)
{
    ioopm_db_t *db = ioopm_create_db();

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0001", "0001", 1));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0001", "A01", 1));

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0002", "0002", 2));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0002", "A02", 2));

    int id1 = ioopm_create_cart(db);
    int id2 = ioopm_create_cart(db);
    CU_ASSERT_TRUE(ioopm_remove_cart(db, id2));

    CU_ASSERT_TRUE(ioopm_add_to_cart(db, id1, "0001", 1));
    CU_ASSERT_TRUE(ioopm_add_to_cart(db, id1, "0002", 2));

    CU_ASSERT_TRUE(ioopm_remove_merch(db, "0001"));

    CU_ASSERT_TRUE(ioopm_checkout(db, id1));

    ioopm_delete_db(db);
}

void test_edit_item_in_cart(void)
{
    ioopm_db_t *db = ioopm_create_db();

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0001", "0001", 1));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0001", "A01", 1));

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0003", "0003", 3));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0003", "A03", 3));

    int id = ioopm_create_cart(db);

    CU_ASSERT_TRUE(ioopm_add_to_cart(db, id, "0001", 1));
    CU_ASSERT_TRUE(ioopm_add_to_cart(db, id, "0003", 1));

    CU_ASSERT_TRUE(ioopm_edit_merch(db, "0001", "0002", "0001", 1));

    CU_ASSERT_TRUE(ioopm_remove_cart(db, id));

    CU_ASSERT_TRUE(ioopm_edit_merch(db, "0002", "0002", "0001", 1));
    CU_ASSERT_TRUE(ioopm_edit_merch(db, "0002", "0001", "0001", 1));

    ioopm_delete_db(db);
}

void test_remove_more_items_than_in_cart(void)
{
    ioopm_db_t *db = ioopm_create_db();

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0001", "0001", 1));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0001", "A01", 1));

    int id = ioopm_create_cart(db);

    CU_ASSERT_TRUE(ioopm_add_to_cart(db, id, "0001", 1));

    CU_ASSERT_FALSE(ioopm_remove_from_cart(db, id, "0001", 2));

    ioopm_delete_db(db);
}

void test_add_more_to_cart_than_in_stock(void)
{
    ioopm_db_t *db = ioopm_create_db();

    CU_ASSERT_TRUE(ioopm_add_merch(db, "0001", "0001", 1));
    CU_ASSERT_TRUE(ioopm_replenish(db, "0001", "A01", 1));

    int id1 = ioopm_create_cart(db);
    int id2 = ioopm_create_cart(db);

    CU_ASSERT_TRUE(ioopm_add_to_cart(db, id1, "0001", 1));
    CU_ASSERT_FALSE(ioopm_add_to_cart(db, id2, "0001", 1));

    ioopm_delete_db(db);
}

int main()
{
    CU_initialize_registry();

    // Databse Tests
    CU_pSuite suite_db = CU_add_suite("Database Test Suite", init_suite, clean_suite);

    CU_add_test(suite_db, "Test: Create & Destroy DB", test_create_destroy_db);
    CU_add_test(suite_db, "Test: Add Merch to DB", test_add_merch);
    CU_add_test(suite_db, "Test: Replenish stock", test_replenish_stock);
    CU_add_test(suite_db, "Test: Remove Merch", test_remove_merch);
    CU_add_test(suite_db, "Test: Edit Merch", test_edit_merch);
    CU_add_test(suite_db, "Test: Create & Destroy Cart", test_create_destroy_cart);
    CU_add_test(suite_db, "Test: Add to Cart", test_add_to_cart);
    CU_add_test(suite_db, "Test: Remove from Cart", test_remove_from_cart);
    CU_add_test(suite_db, "Test: Checkout", test_checkout);
    CU_add_test(suite_db, "Test: Invalid Shelf", test_invalid_shelf);
    CU_add_test(suite_db, "Test: Show Stock, does not exist", test_stock_item_does_not_exist);
    CU_add_test(suite_db, "Test: Replenish stock, does not exist", test_replenish_item_does_not_exist);
    CU_add_test(suite_db, "Test: Edit cart, does not exist", test_edit_cart_does_not_exist);
    CU_add_test(suite_db, "Test: Remove item before checkout", test_remove_item_before_checkout);
    CU_add_test(suite_db, "Test: Edit item in cart", test_edit_item_in_cart);
    CU_add_test(suite_db, "Test: Remove more items than in cart", test_remove_more_items_than_in_cart);
    CU_add_test(suite_db, "Test: Add more to carts than in stock", test_add_more_to_cart_than_in_stock);

    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}
