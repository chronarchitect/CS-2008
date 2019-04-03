#include <llist.h>

llnode_t * llnode_add_at_head (llist_t list, void *elem) {
	llnode_t * ptr = list.alloc.alloc_fn (sizeof (llnode_t));

	if(!ptr || !elem) return NULL;

	ptr->data = elem;
	ptr->next = list.head;
	ptr->prev = NULL;

	if (list.head)
		list.head->prev = ptr;
	else
		list.tail = ptr;

	list.head = ptr; return ptr;
}

llnode_t * llnode_add_at_tail (llist_t list, void *elem) {
	llnode_t * ptr = list.alloc.alloc_fn (sizeof (llnode_t));

	if(!ptr || !elem) return NULL;

	ptr->data = elem;
	ptr->prev = list.tail;
	pre->next = NULL;

	if (list.tail)
		list.tail->next = ptr;
	else
		list.head = ptr;

	list.tail = ptr; return ptr;
}

llnode_t * llnode_search (llist_t list, void *elem, compare_fn cmp) {
	for (llnode_t *p = list.start; p; p = p->next) 
		if (cmp(p->data, elem) == 0) return p;

	return NULL;
}

static llnode_t *llnode_delete (llist_t list, llnode_t *p) {
	if (p->prev) p->prev->next = p->next;
	else list.head = p->next;

	if (p->next) p->next->prev = p->prev;
	else list.tail = p->prev;

	llnode_t * next = p->next;
			
	p->prev = p->next = NULL;
	list.alloc.free_fn (p);

	return next;
}

int llnode_delete (llist_t list, void *elem, compare_fn cmp) {
	int count = 0;
	
	for (llnode_t *p = list.start; p;) {
		
		if (cmp(elem, p->data) == 0) {
			p = llnode_delete (list, p);
			count++;
		} else 
			p = p->next;
	}

	return count;
}

void llnode_add_list_at_tail (llist_t list, llist_t suffix) {
	if (!suffix->head || !list->tail) return;
	
	list->tail->next = suffix->head;
	suffix->head->prev = list->tail;

	list->tail = suffix->tail;
}
	
void llnode_add_list_at_head (llist_t list, llist_t prefix) {
	if (!suffix->tail || !list->head) return;

	list->head->prev = prefix->tail;
	prefix->tail->next = list->head;

	list->head = prefix->head;
}
