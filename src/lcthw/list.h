#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

struct ListNode;
typedef struct ListNode {
	struct ListNode *next;
	struct ListNode *prev;
	void *value;
} ListNode;

typedef struct List {
	int count;
	ListNode *first;
	ListNode *last;
} List;

List *List_create();

void List_destroy(List *list);
void List_clear(List *list);
void List_clear_destroy(List *list);

#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

void List_push(List *list, void *value);
void *List_pop(List *list);

void List_unshift(List *list, void *value);
void *List_shift(List *list);

void *List_remove(List *list, ListNode *node);
void List_swap_nodes(ListNode *node1, ListNode *node2);

int List_is_empty(List *list);
void *List_value_at(List *list, int position);
List *List_insert_value_at(List *list, int position, void *value);
List *List_erase_at(List *list, int position);
void *List_value_n_from_end(List *list, int position);
List *List_reverse(List *list);
void List_remove_value(List *list, void *value);

#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
ListNode *V = NULL;\
for(V = _node = L->S; _node != NULL; V = _node = _node->M)
#endif
