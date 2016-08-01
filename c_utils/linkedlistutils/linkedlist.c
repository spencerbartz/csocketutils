/**********************************************************
 * Title: linkedlist.c
 * Author: Spencer P. Bartz
 * Description: Generic implementation of ring
 * linked list. Callers must provide their own
 * data copying and compare functions.
 **********************************************************/

#include "linkedlist.h"

// Initialize head_node. The head node is a special node that has no data
void init(struct Node * head_node) 
{
    head_node = new_node(id++, NULL);
    head_node->next = head_node;
    head_node->prev = head_node;
}

// Create and insert a new node immediately after the head node
int insert(void * data, struct Node * head_node, int (*copy_data)(void * data, struct Node * head_node))
{
    struct Node * node = find(data);
    if(node == NULL) {
      struct Node * new_node;
      copy_data(data, new_node);
      new_node->next = head_node->next;
      head_node->next = new_node;
      new_node->prev = head_node;
      return 1;
    }
    return 0;
}

// Remove a node from the list
struct Node * remove(void * data)
{
    struct Node * node_to_remove = find(data);
    if(node_to_remove != NULL) {
        node_to_remove->prev->next = node_to_remove->next;
        node_to_remove->next->prev = node_to_remove->prev;
        free(node_to_remove);
    }
    return NULL;
}

// Search the list in O(n) time
struct Node * find(void * data, struct Node * head_node, int (*compare)(void * data, struct Node * cur_node))
{
    struct Node * cur_node = head_node->next;

    while(cur_node != head_node) {
        if(compare(data, cur_node)) {
            return cur_node;
        } 
    }
    return NULL;
}

struct Node * new_node(int id, void * data)
{
    struct Node * p = malloc(sizeof(struct Node));
    p->id = id;
    p->data = data;
    return p;
}
