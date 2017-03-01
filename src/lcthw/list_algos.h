#include "list.h"

typedef int (*List_compare) (const void *a, const void *b);
int List_buble_sort(List *list, List_compare cmp);
List *List_merge_sort(List *list, List_compare cmp);

List *List_merge(List *left, List *right, List_compare cmp);
