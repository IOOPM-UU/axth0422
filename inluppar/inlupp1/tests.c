#include <CUnit/Basic.h>
#include "hash_table.h"
#include "hash_table_iterator.h"
#include "linked_list.h"
#include "list_iterator.h"
#include "common.h"
#include <stddef.h>
#include <string.h>

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

size_t string_knr_hash(elem_t str)
{
  size_t result = 0;
  while (*str.s != '\0')
  {
    result = result * 31 + ((unsigned char)*str.s);
    str.s++;
  }
  return result;
}

bool string_compare(elem_t str1, elem_t str2)
{
  return strcmp(str1.s, str2.s) == 0;
}

void test_create_destroy(void)
{

  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_knr_hash, string_compare);
  CU_ASSERT_PTR_NOT_NULL(ht);
  ioopm_hash_table_destroy(ht);
}

void test_insert_once(void)
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_knr_hash, string_compare);

  char *key = "abc";
  int value = 123;

  // check that key is not in ht
  elem_t result = int_elem(0);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, string_elem(key), &result));
  CU_ASSERT_EQUAL(result.i, 0);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, string_elem(key), int_elem(value));
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, string_elem(key), &result));
  CU_ASSERT_EQUAL(result.i  , value);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_remove_entry(void)
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_knr_hash, string_compare);

  char *key = "pkd";
  int value = 576;

  elem_t result;

  result = ioopm_hash_table_remove(ht, string_elem(key));

  CU_ASSERT_EQUAL(result.i, -1);

  ioopm_hash_table_insert(ht, string_elem(key), int_elem(value));

  result = ioopm_hash_table_remove(ht, string_elem(key));

  CU_ASSERT_EQUAL(value, result.i);

  ioopm_hash_table_destroy(ht);
} 

void test_has_key(void)
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_knr_hash, string_compare);

  char *key = "ioopm";
  int value = 7734;

  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, string_elem(key)));

  ioopm_hash_table_insert(ht, string_elem(key), int_elem(value));

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, string_elem(key)));

  ioopm_hash_table_destroy(ht);
}

void test_is_empty(void)
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_knr_hash, string_compare);

  char *key = "dark";
  int value = 256;

  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

  ioopm_hash_table_insert(ht, string_elem(key), int_elem(value));

  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));

  ioopm_hash_table_destroy(ht);
}

void test_size(void)
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_knr_hash, string_compare);

  char *key = "automata";
  int value = 41;

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

  ioopm_hash_table_insert(ht, string_elem(key), int_elem(value));

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);

  ioopm_hash_table_remove(ht, string_elem(key));

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

  ioopm_hash_table_destroy(ht);
}

void test_iterator_several_entries()
{
  char *keys[3] = {"abc", "qwe", "asd"};
  int values[3] = {0, 1, 2};

  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_knr_hash, string_compare);
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, string_elem(keys[i]), int_elem(values[i]));
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

  ioopm_list_append(list, int_elem(1203));
  int value = ioopm_list_get(list, 0).i;
  CU_ASSERT_EQUAL(value, 1203);

  ioopm_list_append(list, int_elem(101121));
  value = ioopm_list_get(list, 1).i;
  CU_ASSERT_EQUAL(value, 101121);

  ioopm_list_destroy(list);
}

void test_ll_prepend(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_prepend(list, int_elem(1936));
  int value = ioopm_list_get(list, 0).i;
  CU_ASSERT_EQUAL(value, 1936);

  ioopm_list_prepend(list, int_elem(2200));
  value = ioopm_list_get(list, 0).i;
  CU_ASSERT_EQUAL(value, 2200);

  ioopm_list_destroy(list);
}

void test_ll_head_last(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_insert(list, 0, int_elem(20));
  ioopm_list_insert(list, 1, int_elem(50));
  ioopm_list_insert(list, 2, int_elem(100));
  
  int value = ioopm_list_head(list).i;
  CU_ASSERT_EQUAL(value, 20);
  
  value = ioopm_list_last(list).i;
  CU_ASSERT_EQUAL(value, 100);

  ioopm_list_destroy(list);
}

void test_ll_insert_get(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_insert(list, 0, int_elem(20));
  ioopm_list_insert(list, 1, int_elem(50));
  ioopm_list_insert(list, 2, int_elem(100));
  ioopm_list_insert(list, 1, int_elem(25));
  ioopm_list_insert(list, 3, int_elem(75));
  ioopm_list_insert(list, 1, int_elem(22));

  CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 20);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 22);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 2).i, 25);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 3).i, 50);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 4).i, 75);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 5).i, 100);

  ioopm_list_destroy(list);
}

void test_ll_remove(void)
{
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_insert(list, 0, int_elem(111));
  ioopm_list_insert(list, 1, int_elem(222));
  ioopm_list_insert(list, 2, int_elem(333));
  ioopm_list_insert(list, 3, int_elem(444));
  ioopm_list_insert(list, 4, int_elem(555));
  ioopm_list_insert(list, 5, int_elem(666));
  ioopm_list_insert(list, 6, int_elem(777));

  int value = ioopm_list_remove(list, 0).i;
  CU_ASSERT_EQUAL(value, 111);

  value = ioopm_list_remove(list, 5).i;
  CU_ASSERT_EQUAL(value, 777);

  value = ioopm_list_remove(list, 1).i;
  CU_ASSERT_EQUAL(value, 333);

  value = ioopm_list_remove(list, 1).i;
  CU_ASSERT_EQUAL(value, 444);

  ioopm_list_destroy(list);
}

void test_ll_is_empty(void)
{
  ioopm_list_t *list = ioopm_list_create();

  CU_ASSERT_TRUE(ioopm_list_is_empty(list));

  ioopm_list_insert(list, 0, int_elem(111));

  CU_ASSERT_FALSE(ioopm_list_is_empty(list));

  ioopm_list_insert(list, 1, int_elem(222));

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
    ioopm_list_append(ll, int_elem(values[i]));
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

size_t ll_hash(elem_t ll)
{
  return (size_t) ll.p;
}

bool ll_compare(elem_t ll1, elem_t ll2)
{
  return ll1.p == ll2.p;
}

void test_union(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ll_hash, ll_compare);

  ioopm_list_t *list1 = ioopm_list_create();

  ioopm_list_insert(list1, 0, int_elem(111));
  ioopm_list_insert(list1, 1, int_elem(222));
  ioopm_list_insert(list1, 2, int_elem(333));

  ioopm_hash_table_insert(ht, ptr_elem(list1), ptr_elem(list1));
  
  ioopm_list_t *list2 = ioopm_list_create();
  
  ioopm_list_insert(list2, 0, int_elem(444));
  ioopm_list_insert(list2, 1, int_elem(555));
  ioopm_list_insert(list2, 2, int_elem(666));
  ioopm_list_insert(list2, 3, int_elem(777));


  ioopm_hash_table_insert(ht, ptr_elem(list2), ptr_elem(list2));

  ioopm_hash_table_insert(ht, ptr_elem(list1), ptr_elem(list2));

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 2);

  ioopm_list_destroy(list1);
  
  ioopm_list_destroy(list2);

  ioopm_hash_table_destroy(ht);
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

  // Union Tests
  CU_pSuite suite_union = CU_add_suite("Union Test Suite", init_suite, clean_suite);

  CU_add_test(suite_union, "Union Test", test_union);

  CU_basic_set_mode(CU_BRM_VERBOSE);

  CU_basic_run_tests();

  CU_cleanup_registry();
  return CU_get_error();
}