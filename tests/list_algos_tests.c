#include "minunit.h"
#include "../src/lcthw/list_algos.h"
#include "../src/lcthw/list.h"
#include <assert.h>
#include <string.h>
#include <sys/time.h>

char *values[] = { "XXXX", "1234", "abcd", "xjvef", "NDSS" };

#define NUM_VALUES 5

List *create_words()
{
  int i = 0;
  List *words = List_create();

  for (i = 0; i < NUM_VALUES; i++) {
    List_push(words, values[i]);
  }

  return words;
}

int is_sorted(List *words)
{
  LIST_FOREACH(words, first, next, cur) {
    if (cur->next && strcmp(cur->value, cur->next->value) > 0) {
      debug("%s %s", (char *)cur->value, (char *)cur->next->value);
      return 0;
    }
  }

  return 1;
}

char *test_buble_sort()
{
  List *words = create_words();

  // should work on a list that needs sorting
  int rc = List_buble_sort(words, (List_compare) strcmp);
  mu_assert(rc == 0, "Buble sort failed");
  mu_assert(is_sorted(words), "Words are not sorted after buble sort");

  // should work on already sorted list
  rc = List_buble_sort(words, (List_compare) strcmp);
  mu_assert(rc == 0, "Buble sort of already sorted failed");
  List_destroy(words);

  // should work on empty list
  words = List_create(words);
  rc = List_buble_sort(words, (List_compare) strcmp);
  mu_assert(rc == 0, "Buble sort failed on empty list");
  mu_assert(is_sorted(words), "Words should be sorted if empty");

  List_destroy(words);

  return NULL;
}

char *test_merge_sort()
{
  List *words = create_words();

  // should work on a list that needs sorting
  List *res = List_merge_sort(words, (List_compare) strcmp);
  mu_assert(is_sorted(res), "Words are not sorted after merge sort");

  List *res2 = List_merge_sort(res, (List_compare) strcmp);
  mu_assert(is_sorted(res), "Should still be sorted after merge sort")

  List_destroy(res2);
  List_destroy(res);

  List_destroy(words);

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_buble_sort);
  mu_run_test(test_merge_sort);

  return NULL;
}

RUN_TESTS(all_tests);
