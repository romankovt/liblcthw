#ifndef darray_algos_h
#define darray_algos_h
#include "darray.h"

typedef int (*DArray_compare)(const void *a, const void *b);

int DArray_qsort(DArray *array, DArray_compare cmp);
int DArray_heapsort(DArray *array, DArray_compare cmp);
int DArray_mergesort(DArray *array, DArray_compare cmp);

void DArray_qsort_iterator(DArray *array, DArray_compare cmp, int start, int end);
DArray *DArray_mergesort_iterator(DArray *array, DArray_compare cmp);

void DArray_swap(DArray *array, int index1, int index2);
DArray *DArray_merge(DArray *left, DArray* right, DArray_compare cmp);

void *DArray_parent(DArray *array, int i);
void *DArray_left_child(DArray *array, int i);
void *DArray_right_child(DArray *array, int i);

void *DArray_heapify(DArray *array, int end, DArray_compare cmp);
void *DArray_balance_node(DArray *array, int head, DArray_compare cmp);
void *Heap_delete_max(DArray *array, int end, DArray_compare cmp);
#endif
