#include "minunit.h"
#include "../src/lcthw/list.h"
#include <assert.h>

static List *list = NULL;
static List *empty_list = NULL;
char*test1 = "test1 data";
char*test2 = "test2 data";
char*test3 = "test3 data";

char *test_create()
{
  list = List_create();
  mu_assert(list != NULL, "Failed to create a list");

  return NULL;
}

char *test_destroy()
{
  List_clear_destroy(list);

  return NULL;
}

char *test_push_pop()
{
  List_push(list, test1);
  mu_assert(List_last(list) == test1, "Wrong last value");

  List_push(list, test2);
  mu_assert(List_last(list) == test2, "Wrong last value");

  List_push(list, test3);
  mu_assert(List_last(list) == test3, "Wrong last value");

  mu_assert(List_count(list) == 3, "Wrong count on push");

  char *val = List_pop(list);
  mu_assert(val == test3, "Wrong value on pop");

  val = List_pop(list);
  mu_assert(val == test2, "Wrong value on pop");

  val = List_pop(list);
  mu_assert(val == test1, "Wrong value on pop");

  mu_assert(List_count(list) == 0, "Wrong count on pop");

  return NULL;
}

char *test_unshift()
{
  List_unshift(list, test1);
  mu_assert(List_first(list) == test1, "Wrong first value");

  List_unshift(list, test2);
  mu_assert(List_first(list) == test2, "Wrong first value");

  List_unshift(list, test3);
  mu_assert(List_first(list) == test3, "Wrong first value");
  mu_assert(List_count(list) == 3, "Wrong list count on unshift");

  return NULL;
}

char *test_remove()
{
  // We only need to test the middle remove case since push/shist
  // already tests the other cases
  char *val = List_remove(list, list->first->next);

  mu_assert(val == test2, "Wrong removed element");
  mu_assert(List_count(list) == 2, "Wrong count on remove element");
  mu_assert(List_first(list) == test3, "Wrong the first element");
  mu_assert(List_last(list) == test1, "Wrong the last element after remove");

  return NULL;
}

char *test_shift()
{
  mu_assert(List_count(list) != 0, "Wrong count before shift");

  char *val = List_shift(list);
  mu_assert(val == test3, "Wrong value on a shift");

  val = List_shift(list);
  mu_assert(val == test1, "Wrong value on shift");
  mu_assert(List_count(list) == 0, "Wrong count after shift");

  return NULL;
}

char *test_is_empty()
{
  list = List_create();
  mu_assert(List_is_empty(list) == 1, "List should be empty");

  List_push(list, "Some word");
  mu_assert(List_is_empty(list) == 0, "List should not be empty");
  return NULL;
}

char *test_value_at()
{
  list = List_create();
  empty_list = List_create();
  List_push(list, "Some word");

  mu_assert(List_value_at(list, 0) == "Some word", "List should not be empty");

  mu_assert(List_value_at(list, 10) == NULL, "Should return NULL if doesn't have this position");

  mu_assert(List_value_at(empty_list, 0) == NULL, "Should return NULL if has empty list");
  return NULL;
}

char *test_insert_value_at()
{
  list = List_create();
  List_push(list, "Some word");
  List_insert_value_at(list, 0, "another word");

  mu_assert(list->first->value == "another word", "List didn't insert new value");

  return NULL;
}

char *test_erase_at()
{
  list = List_create();
  List_push(list, "Some word");
  List_push(list, "Some word2");

  List_erase_at(list, 1);
  mu_assert(list->count == 1, "List should have decremented count");
  mu_assert(list->last->value == "Some word", "List should have removed first node");

  List_erase_at(list, 0);
  mu_assert(list->count == 0, "List should have decremented count");

  List_erase_at(list, 0);
  mu_assert(list->count == 0, "Does nothing if list has 0 elements");

  return NULL;
}

char *test_value_n_from_end()
{
  list = List_create();
  empty_list = List_create();

  List_push(list, "Some word");
  List_push(list, "Some word2");

  mu_assert(List_value_n_from_end(list, 1) == "Some word", "Should return first element");
  mu_assert(List_value_n_from_end(list, 0) == "Some word2", "Should return last element");

  mu_assert(List_value_n_from_end(empty_list, 0) == NULL, "Should return NULL");
  return NULL;
}

char *test_reverse()
{
  list = List_create();
  empty_list = List_create();

  List_push(list, "Some word");
  List_push(list, "Some word2");
  List_push(list, "Some word3");
  List_push(list, "Some word4");
  List_push(list, "Some word5");

  list = List_reverse(list);
  mu_assert(list->first->value == "Some word5", "Wasn't reversed");

  list = List_reverse(list);
  mu_assert(list->first->value == "Some word", "Wasn't reversed");

  empty_list = List_reverse(empty_list);
  mu_assert(empty_list->first == NULL, "Didn't handle empty");

  return NULL;
}

char *test_remove_by_value()
{
  list = List_create();
  empty_list = List_create();

  List_push(list, "Some word");
  List_push(list, "Some word2");
  List_push(list, "Some word3");

  List_remove_value(list, "Some word");
  mu_assert(list->first->value == "Some word2", "Value wasn't removed");
  mu_assert(list->count == 2, "Changes count");

  List_remove_value(list, "some gibberish");
  mu_assert(list->first->value == "Some word2", "Don't remove value which doesn't exist");

  List_remove_value(empty_list, "some gibberish");
  mu_assert(empty_list->first == NULL, "Doesn't work fine with empty list");

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_create);
  mu_run_test(test_push_pop);
  mu_run_test(test_unshift);
  mu_run_test(test_remove);
  mu_run_test(test_shift);
  mu_run_test(test_destroy);
  mu_run_test(test_is_empty);
  mu_run_test(test_value_at);
  mu_run_test(test_insert_value_at);
  mu_run_test(test_erase_at);
  mu_run_test(test_value_n_from_end);
  mu_run_test(test_reverse);
  mu_run_test(test_remove_by_value);

  return NULL;
}

RUN_TESTS(all_tests);
