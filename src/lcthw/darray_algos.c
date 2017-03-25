#include "darray_algos.h"
#include <stdlib.h>
int DArray_mergesort(DArray *array, DArray_compare cmp)
{
  array->contents = DArray_mergesort_iterator(array, cmp)->contents;

  return 0;
}

int DArray_qsort(DArray *array, DArray_compare cmp)
{
  DArray_qsort_iterator(array, cmp, 0, array->end - 1);

  return 0;
}

DArray *DArray_mergesort_iterator(DArray *array, DArray_compare cmp)
{
  if (DArray_count(array) == 1) {
    return array;
  }

  int middle_position = DArray_count(array) / 2;
  DArray *left = DArray_create(sizeof(void *), middle_position);
  DArray *right = DArray_create(sizeof(void *), DArray_count(array) - middle_position);

  for(int i = 0; i < DArray_count(array); i++) {
    i < middle_position ? DArray_push(left, array->contents[i]) : DArray_push(right, array->contents[i]);
  }

  return DArray_merge(DArray_mergesort_iterator(left, cmp), DArray_mergesort_iterator(right, cmp), cmp);
}

void DArray_qsort_iterator(DArray *array, DArray_compare cmp, int start, int end)
{
  int pivot_position = start;

  if (start < end) {
    for(int i = start + 1; i <= end; i++) {
      if (cmp(DArray_get(array, i), DArray_get(array, pivot_position)) < 0) {
        if (i - pivot_position > 1) {
          DArray_swap(array, pivot_position, pivot_position + 1);
          DArray_swap(array, pivot_position, i);
          pivot_position++;
        } else {
          DArray_swap(array, pivot_position, pivot_position + 1);
          pivot_position++;
        }
      }
    }

    DArray_qsort_iterator(array, cmp, start, pivot_position - 1);
    DArray_qsort_iterator(array, cmp, pivot_position + 1, end);
  }
}

void DArray_swap(DArray *array, int index1, int index2)
{
  void *temp = array->contents[index1];
  array->contents[index1] = array->contents[index2];
  array->contents[index2] = temp;
}

DArray *DArray_merge(DArray *left, DArray *right, DArray_compare cmp) {
  DArray *sorted = DArray_create(sizeof(void *), DArray_count(left) + DArray_count(right));
  int l_cur = 0;
  int r_cur = 0;

  while(l_cur < left->end && r_cur < right->end) {
    if (cmp(DArray_get(left, l_cur), DArray_get(right, r_cur)) <= 0) {
      DArray_push(sorted, left->contents[l_cur]);
      l_cur++;
    } else {
      DArray_push(sorted, right->contents[r_cur]);
      r_cur++;
    }
  }

  while(l_cur < left->end) {
    DArray_push(sorted, left->contents[l_cur]);
    l_cur++;
  }

  while(r_cur < right->end) {
    DArray_push(sorted, right->contents[r_cur]);
    r_cur++;
  }

  DArray_free(left);
  DArray_free(right);
  return sorted;
}

int DArray_heapsort(DArray *array, DArray_compare cmp) {
  DArray_heapify(array, array->end, cmp);

  for(int i = array->end - 1; i > 0; i--) {
    Heap_delete_max(array, i, cmp);
  }

  array->contents = array->contents;
  return 0;
}

void *DArray_left_child(DArray *array, int i) {
  if (2*i < array->end )
    return array->contents[2*i + 1];
  else {
    return NULL;
  }
}

void *DArray_right_child(DArray *array, int i) {
  if ((2*i + 1) < array->end )
    return array->contents[2*i + 2];
  else {
    return NULL;
  }
}

void *DArray_parent(DArray *array, int i) {
  if (i == 0)
    return NULL;
  return array->contents[(i-1)/2];
}

void *DArray_heapify(DArray *array, int end, DArray_compare cmp) {
  int left_end_index = ((end - 1) / 2) - 1;

  for(int i = left_end_index; i >= 0; i--) {
    DArray_balance_node(array, i, cmp);
  }

  return NULL;
}

void *DArray_balance_node(DArray *array, int head, DArray_compare cmp) {
  void *left_child = DArray_left_child(array, head);
  void *right_child = DArray_right_child(array, head);
  int biggest_child_index;

  if (right_child != NULL && cmp(left_child, right_child) < 0) {
    biggest_child_index = 2*head + 2;
  } else {
    biggest_child_index = 2*head + 1;
  }

  if (cmp(DArray_get(array, head), DArray_get(array, biggest_child_index)) < 0) {
    DArray_swap(array, head, biggest_child_index);
  }

  if ((biggest_child_index * 2 + 1) < array->end) {
    DArray_balance_node(array, biggest_child_index, cmp);
  }
  return NULL;
}

void *Heap_delete_max(DArray *array, int end, DArray_compare cmp) {
  DArray_swap(array, 0, end);

  int i = 0;
  int had_bigger_child = 1;
  int biggest_child_index;
  void *left_child;
  void *right_child;

  while(had_bigger_child > 0) {
    had_bigger_child = 0;
    if (2*i + 1 < end) {
      left_child = DArray_left_child(array, i);

      if (2*i + 2 < end) {
        right_child = DArray_right_child(array, i);

        if (cmp(left_child, right_child) > 0) {
          biggest_child_index = 2*i + 1;
        } else {
          biggest_child_index = 2*i + 2;
        }
      } else {
        biggest_child_index = 2*i + 1;
      }

      if (cmp(DArray_get(array, i), DArray_get(array, biggest_child_index)) < 0) {
        DArray_swap(array, i, biggest_child_index);
        i = biggest_child_index;
        had_bigger_child = 1;
      }
    }
  }

  return NULL;
}
