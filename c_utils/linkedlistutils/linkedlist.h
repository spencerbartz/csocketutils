#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stddef.h>
#include <stdlib.h>

struct Node {
    struct Node * next;
    struct Node * prev;
    int id;
    void * data;
};

static int ELEMENT_EXISTS    = 100;
static int ELEMENT_NOT_FOUND = 101;
static int SUCCESS           = 102;

void init(struct Node * head_node);
int insert(void * data, struct Node * head_node, int (*copy_data)(void * data, struct Node * head_node));
struct Node * remove(void * data);
struct Node * find(void * data, struct Node * head_node, int (*compare)(void * data, struct Node * cur_node));
struct Node * new_node(int id, void * data);

int id = 0;

#endif
