#include "darray_algos.h"
#include <stdlib.h>
void print_array(DArray *array)
{
  for(int i = 0; i < array->end; i++) {
  }
}

int DArray_heapsort(DArray *array, DArray_compare cmp)
{
  return heapsort(array->contents, DArray_count(array), sizeof(void *), cmp);
}

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
      if (strcmp(DArray_get(array, i), DArray_get(array, pivot_position)) < 0) {
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
