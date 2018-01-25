//
//  list.h
//  Singly Linked List
//
//  Created by Cristina Silva on 28/12/17.
//  Copyright © 2017 Cristina Silva. All rights reserved.
//

#ifndef list_h
#define list_h

#include "definitions.h"

typedef struct node {
    int data;
    struct node* next;
} node_t;

node_t* node_init(const int);

typedef struct list {
    node_t* head;
    void (*destroy)(struct list*);
    void (*to_string)(const struct list*);
    int (*get_length)(const struct list*);
    node_t* (*get_node_at)(const struct list*, const int);
    node_t* (*get_head)(const struct list*);
    node_t* (*get_tail)(const struct list*);
    struct list* (*set_head)(struct list*, node_t*);
    struct list* (*set_tail)(struct list*, node_t*);
    struct list* (*insert_at_beg)(struct list*, const int);
    struct list* (*insert_at_end)(struct list*, const int);
    struct list* (*insert_at)(struct list*, const int, const unsigned int);
    struct list* (*delete_at_beg)(struct list*);
    struct list* (*delete_at_end)(struct list*);
} list_t;

list_t* list_init(void);

#endif /* list_h */
