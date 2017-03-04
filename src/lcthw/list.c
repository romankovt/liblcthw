#include "list.h"
#include "list_algos.h"
#include "dbg.h"

List *List_create()
{
  return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
  LIST_FOREACH(list, first, next, cur) {
    if (cur->prev) {
      free(cur->prev);
    }
  }

  free(list->last);
  free(list);
}

void List_clear(List * list)
{
  LIST_FOREACH(list, first, next, cur) {
    free(cur->value);
  }
}


void List_clear_destroy(List * list)
{
  List_clear(list);
  List_destroy(list);
}


void List_push(List * list, void *value)
{
  ListNode *node  = calloc(1, sizeof(ListNode));
  check_mem(node);

  node->value = value;

  if (list->last == NULL) {
    list->first = node;
    list->last = node;
  } else {
    list->last->next = node;
    node->prev = list->last;
    list->last = node;
  }

  list->count++;

  error:
    return;
}

void *List_pop(List *list)
{
  ListNode *node = list->last;
  return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List * list, void *value)
{
  ListNode *node = calloc(1, sizeof(ListNode));
  check_mem(node);

  node->value = value;

  if (list->first == NULL) {
    list->first = node;
    list->last = node;
  } else {
    node->next = list->first;
    list->first->prev = node;
    list->first = node;
  }

  list->count++;

  error:
    return;
}

void *List_shift(List * list)
{
  ListNode *node = list->first;
  return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
  void *result = NULL;

  check(list->first && list->last, "List is empty");
  check(node, "Can't be NULL");

  if (node == list->first && node == list->last) {
    list->first = NULL;
    list->last = NULL;
  } else if (node == list->first) {
    list->first = node->next;
    check(list->first != NULL, "Invalid list somehow got first NULL");
    list->first->prev = NULL;
  } else if (node == list->last) {
    list->last = node->prev;
    check(list->last != NULL, "Invalid list somehow got a last that is null");
    list->last->next = NULL;
  } else {
    ListNode *after = node->next;
    ListNode *before = node->prev;

    before->next = after;
    after->prev = before;
  }

  list->count--;
  result = node->value;
  free(node);

  error:
    return result;
}

void print_all_of_them(List *list) {
  LIST_FOREACH(list, first, next, cur) {
    printf("%s ", (char *)cur->value);
  }
  printf("\n");
}

List *List_merge_sort(List *list, List_compare cmp) {
  // consist of 1 element, so it is sorted
  if (list->count == 1) {
    return list;
  }

  List *left = List_create();
  List *right = List_create();

  int i = 0;
  LIST_FOREACH(list, first, next, cur) {
    i < (list->count / 2) ? List_push(left, cur->value) : List_push(right, cur->value);
    i++;
  }

  // recursively split array till the very end
  return List_merge(List_merge_sort(left, cmp), List_merge_sort(right, cmp), cmp);
}

List *List_merge(List *left, List *right, List_compare cmp) {
  List *sorted = List_create();

  while(left->count > 0 && right->count > 0) {
    if (cmp((char *)left->first->value, (char *)right->first->value) <= 0) {
      List_push(sorted, left->first->value);
      List_shift(left);
    } else {
      List_push(sorted, right->first->value);
      List_shift(right);
    }
  }

  // merge if something left after loop
  while(left->count != 0) {
    List_push(sorted, left->first->value);
    List_shift(left);
  }

  while(right->count != 0) {
    List_push(sorted, right->first->value);
    List_shift(right);
  }

  // Clean-up
  List_destroy(left);
  List_destroy(right);

  return sorted;
}

int List_buble_sort(List *list, List_compare cmp) {
  if (list->first == NULL || list->last == NULL) {
    // it's has either one or no element so it's already sorted
    return 0;
  }

  int is_sorted = 0;
  while(is_sorted == 0) {
    is_sorted = 1;

    LIST_FOREACH(list, first, next, cur) {
      // skip the last one
      if (cur == list->last) {
        continue;
      }

      if (cmp((char *)cur->value, (char *)cur->next->value) > 0) {
        is_sorted = 0;
        List_swap_nodes(cur, cur->next);
      }
    }
  }

  return 0;
}

void List_swap_nodes(ListNode *node1, ListNode *node2) {
  // do nothing if nodes are the same
  if (node1 == node2) {
    return;
  }

  // don't swap if one element is NULL
  if (node1 == NULL || node2 == NULL) {
    return;
  }

  void *temp = node1->value;
  node1->value = node2->value;
  node2->value = temp;
}

int List_is_empty(List *list) {
  return list->count == 0 ? 1 : 0;
}

void* List_value_at(List *list, int position) {
  if (list->count <= position) {
    return NULL;
  }

  int i = 0;
  void* pointer_to_value = NULL;
  LIST_FOREACH(list, first, next, cur) {
    if (i == position) {
      pointer_to_value = cur->value;
    }
  }

  return pointer_to_value;
}

List *List_insert_value_at(List *list, int position, void *value) {
  int i = 0;

  LIST_FOREACH(list, first, next, cur) {
    if (i == position) {
      cur->value = value;
    }
  }

  return list;
}

List *List_erase_at(List *list, int position) {
  if (position > list->count || list->count == 0) {
    return list;
  }

  int i = 0;

  LIST_FOREACH(list, first, next, cur) {
    if (i == position) {
      list = List_remove(list, cur);
    }

    i++;
  }

  return list;
}

void *List_value_n_from_end(List *list, int position) {
  if (list->count == 0) {
    return NULL;
  }

  ListNode *node = list->last;
  void *found_value = NULL;

  for(int i = 0; node != NULL; node = node->prev, i++) {
    if(position == i) {
      found_value = node->value;
    }
  }

  return found_value;
}

List *List_reverse(List *list) {
  if (list->count == 0) {
    return list;
  }

  ListNode *temp_node = NULL;
  ListNode *current = list->first;

  while(current != NULL) {
    temp_node = current->prev;
    current->prev = current->next;
    current->next = temp_node;
    current = current->prev;
  }

  temp_node = list->first;
  list->first = list->last;
  list->last = temp_node;

  return list;
}

void List_remove_value(List *list, void *value) {
  LIST_FOREACH(list, first, next, cur) {
    if(cur->value == value) {
      List_remove(list, cur);
    }
  }
}
