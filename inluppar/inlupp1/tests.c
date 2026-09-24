#include <CUnit/Basic.h>
#include "hash_table.h"
#include "hash_table_iterator.h"
#include "linked_list.h"
#include "list_iterator.h"
#include <stdio.h>

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

void test_create_destroy(void)
{

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_PTR_NOT_NULL(ht);
  ioopm_hash_table_destroy(ht);
}

void test_insert_once(void)
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int value = 123;

  // check that key is not in ht
  int result = 0;
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, 0);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_remove_entry(void)
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "pkd";
  int value = 576;

  int result;

  result = ioopm_hash_table_remove(ht, key);

  CU_ASSERT_EQUAL(result, -1);

  ioopm_hash_table_insert(ht, key, value);

  result = ioopm_hash_table_remove(ht, key);

  CU_ASSERT_EQUAL(value, result);

  ioopm_hash_table_destroy(ht);
}

void test_has_key(void)
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "ioopm";
  int value = 7734;

  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key));

  ioopm_hash_table_insert(ht, key, value);

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));

  ioopm_hash_table_destroy(ht);
}

void test_is_empty(void)
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "dark";
  int value = 256;

  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

  ioopm_hash_table_insert(ht, key, value);

  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));

  ioopm_hash_table_destroy(ht);
}

void test_size(void)
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "automata";
  int value = 41;

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

  ioopm_hash_table_insert(ht, key, value);

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);

  ioopm_hash_table_remove(ht, key);

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

  ioopm_hash_table_destroy(ht);
}

void test_iterator_several_entries()
{
  char *keys[3] = {"abc", "qwe", "asd"};
  int values[3] = {0, 1, 2};

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  int iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
  CU_ASSERT_EQUAL(iteration_count, 3);
}

void test_ll_create_destroy(void)
{
  ioopm_list_t *list = ioopm_list_create();
  CU_ASSERT_PTR_NOT_NULL(list);
  ioopm_list_destroy(list);
}

void test_ll_append(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_append(list, 1203);
  int value = ioopm_list_get(list, 0);
  CU_ASSERT_EQUAL(value, 1203);

  ioopm_list_append(list, 101121);
  value = ioopm_list_get(list, 1);
  CU_ASSERT_EQUAL(value, 101121);

  ioopm_list_destroy(list);
}

void test_ll_prepend(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_prepend(list, 1936);
  int value = ioopm_list_get(list, 0);
  CU_ASSERT_EQUAL(value, 1936);

  ioopm_list_prepend(list, 2200);
  value = ioopm_list_get(list, 0);
  CU_ASSERT_EQUAL(value, 2200);

  ioopm_list_destroy(list);
}

void test_ll_head_last(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_insert(list, 0, 20);
  ioopm_list_insert(list, 1, 50);
  ioopm_list_insert(list, 2, 100);
  
  int value = ioopm_list_head(list);
  CU_ASSERT_EQUAL(value, 20);
  
  value = ioopm_list_last(list);
  CU_ASSERT_EQUAL(value, 100);

  ioopm_list_destroy(list);
}

void test_ll_insert_get(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_insert(list, 0, 20);
  ioopm_list_insert(list, 1, 50);
  ioopm_list_insert(list, 2, 100);
  ioopm_list_insert(list, 1, 25);
  ioopm_list_insert(list, 3, 75);
  ioopm_list_insert(list, 1, 22);

  CU_ASSERT_EQUAL(ioopm_list_get(list, 0), 20);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 1), 22);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 2), 25);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 3), 50);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 4), 75);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 5), 100);

  ioopm_list_destroy(list);
}

void test_ll_remove(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_insert(list, 0, 111);
  ioopm_list_insert(list, 1, 222);
  ioopm_list_insert(list, 2, 333);
  ioopm_list_insert(list, 3, 444);
  ioopm_list_insert(list, 4, 555);
  ioopm_list_insert(list, 5, 666);
  ioopm_list_insert(list, 6, 777);

  int value = ioopm_list_remove(list, 0);
  CU_ASSERT_EQUAL(value, 111);

  value = ioopm_list_remove(list, 5);
  CU_ASSERT_EQUAL(value, 777);

  value = ioopm_list_remove(list, 1);
  CU_ASSERT_EQUAL(value, 333);

  value = ioopm_list_remove(list, 1);
  CU_ASSERT_EQUAL(value, 444);

  ioopm_list_destroy(list);
}

void test_ll_is_empty(void)
{
  ioopm_list_t *list = ioopm_list_create();

  CU_ASSERT_TRUE(ioopm_list_is_empty(list));

  ioopm_list_insert(list, 0, 111);

  CU_ASSERT_FALSE(ioopm_list_is_empty(list));

  ioopm_list_insert(list, 1, 222);

  CU_ASSERT_FALSE(ioopm_list_is_empty(list));

  ioopm_list_remove(list, 1);

  CU_ASSERT_FALSE(ioopm_list_is_empty(list));

  ioopm_list_remove(list, 0);

  CU_ASSERT_TRUE(ioopm_list_is_empty(list));

  ioopm_list_destroy(list);
}

void test_ll_iterator_several_entries()
{
  int values[3] = {99, 200, 3754};

  ioopm_list_t *ll = ioopm_list_create();
  for (int i = 0; i < 3; i++)
  {
    ioopm_list_append(ll, values[i]);
  }

  int iteration_count = 0;

  ioopm_list_iterator_t *it = ioopm_list_iterator_create(ll);
  while (!ioopm_list_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_list_iterator_advance(it);
  }

  ioopm_list_iterator_destroy(it);
  ioopm_list_destroy(ll);
  CU_ASSERT_EQUAL(iteration_count, 3);
}

int main()
{
  CU_initialize_registry();

  // Hash table Tests
  CU_pSuite suite_ht = CU_add_suite("Hash Table Test Suite", init_suite, clean_suite);

  CU_add_test(suite_ht, "Create & Destroy Test", test_create_destroy);
  CU_add_test(suite_ht, "Insert Once Test", test_insert_once);
  CU_add_test(suite_ht, "Remove Entry Test", test_remove_entry);
  CU_add_test(suite_ht, "Has Key Test", test_has_key);
  CU_add_test(suite_ht, "Is Empty Test", test_is_empty);
  CU_add_test(suite_ht, "Size Test", test_size);
  CU_add_test(suite_ht, "Iterator Test", test_iterator_several_entries);

  // Linked List Tests
  CU_pSuite suite_ll = CU_add_suite("Linked List Test Suite", init_suite, clean_suite);

  CU_add_test(suite_ll, "Linked List: Create & Destroy Test", test_ll_create_destroy);
  CU_add_test(suite_ll, "Linked List: Append Test", test_ll_append);
  CU_add_test(suite_ll, "Linked List: Prepend Test", test_ll_prepend);
  CU_add_test(suite_ll, "Linked List: Head & Last Test", test_ll_head_last);
  CU_add_test(suite_ll, "Linked List: Insert & Get Test", test_ll_insert_get);
  CU_add_test(suite_ll, "Linked List: Remove Test", test_ll_remove);
  CU_add_test(suite_ll, "Linked List: Is Empty Test", test_ll_is_empty);
  CU_add_test(suite_ll, "Linked List: Iterator Test", test_ll_iterator_several_entries);

  CU_basic_set_mode(CU_BRM_VERBOSE);

  CU_basic_run_tests();

  CU_cleanup_registry();
  return CU_get_error();
}