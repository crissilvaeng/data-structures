//
//  list.c
//  Singly Linked List
//
//  Created by Cristina Silva on 28/12/17.
//  Copyright © 2017 Cristina Silva. All rights reserved.
//

#define foreach(node, list) \
    for(node_t* node = list->head; node != NULL; node = node->next)

#include "list.h"
#include <mm_malloc.h>
#include <stdio.h>

static void node_destroy(node_t* self) {
    free(self);
}

static bool node_is_empty(const node_t* self) {
    return self == NULL;
}

static bool node_has_next(const node_t* self) {
    return node_is_empty(self) != TRUE && self->next != NULL;
}

void node_to_string(const node_t* self) {
    if(node_is_empty(self) != TRUE) {
        printf("%d ", self->data);
    }
}

void list_destroy(list_t* self) {
    foreach(node, self) {
        node_destroy(node);
    }
    free(self);
}

void list_to_string(const list_t* self) {
    foreach(node, self) {
        node_to_string(node);
    }
    printf("\n");
}

static bool list_is_null(const list_t* self) {
    return self == NULL;
}

static bool list_is_empty(const list_t* self) {
    return node_is_empty(self->head);
}

static bool list_is_null_or_empty(const list_t* self) {
    return list_is_null(self) || list_is_empty(self);
}

int list_get_length(const list_t* self) {
    int count = 0;
    if (list_is_null_or_empty(self) != TRUE) {
        foreach(node, self) {
            count++;
        }
    }
    return count;
}

node_t* list_get_node_at(const list_t* self, const int index) {
    node_t* current = NULL;
    if (list_is_null_or_empty(self) != TRUE) {
        int count = 0;
        foreach(node, self) {
            if (count == index) {
                current = node;
                break;
            }
            count++;
        }
    }
    return current;
}

node_t* list_get_head(const list_t* self) {
    node_t* head = NULL;
    if (list_is_null_or_empty(self) != TRUE) {
        head = self->head;
    }
    return head;
}

node_t* list_get_tail(const list_t* self) {
    node_t* tail = NULL;
    if (list_is_null_or_empty(self) != TRUE) {
        foreach(node, self) {
            tail = node;
        }
    }
    return tail;
}

list_t* list_set_head(list_t* self, node_t* head) {
    if (list_is_null(self) != TRUE && node_is_empty(head) != TRUE) {
        if (list_is_empty(self) == TRUE) {
            self->head = head;
        } else {
            head->next = self->head;
            self->head = head;
        }
    }
    return self;
}

list_t* list_set_tail(list_t* self, node_t* tail) {
    if (list_is_null(self) != TRUE && node_is_empty(tail) != TRUE) {
        node_t* current = self->get_tail(self);
        if (list_is_empty(self) == TRUE) {
            self->set_head(self, tail);
        } else {
            current->next = tail;
        }
    }
    return self;
}

list_t* list_insert_at_beg(list_t* self, const int data) {
    node_t* node = node_init(data);
    if (list_is_null_or_empty(self) == TRUE) {
        self->head = node;
        return self;
    }
    node->next = self->head;
    self->head = node;
    return self;
}

list_t* list_insert_at_end(list_t* self, const int data) {
    node_t* node = node_init(data);
    if (list_is_null_or_empty(self) == TRUE) {
        self->head = node;
        return self;
    }
    node_t* current = self->head;
    while (node_has_next(current) == TRUE) {
        current = current->next;
    }
    current->next = node;
    return self;
}

list_t* list_insert_at(list_t* self, const int data, unsigned int index) { // BUG!
    if (list_is_null_or_empty(self) && index == 0) {
        self->head = node_init(data);
        return self;
    }
    int i = 0;
    node_t* current = self->head;
    for (i = 1; i < index; i++) {
        current = current->next;
        if (current == NULL) break;
    }
    node_t* node = node_init(data);
    if (i == index && node_has_next(current)) {
        node->next = current;
    } else if (i == index && current == NULL) {
        current = node;
    }
    return self;
}

list_t* list_delete_at_beg(list_t* self) {
    if (list_is_null_or_empty(self) == TRUE) {
        return self;
    }
    node_t* head = self->head->next;
    node_destroy(self->head);
    self->head = head;
    return self;
}

list_t* list_delete_at_end(list_t* self) {
    if (list_is_null_or_empty(self) == TRUE) {
        return self;
    }
    node_t* current = self->head;
    node_t* previous = NULL;
    while (node_has_next(current) == TRUE) {
        previous = current;
        current = current->next;
    }
    previous->next = NULL;
    node_destroy(current);
    return self;
}

node_t* node_init(const int data) {
    node_t* node = malloc(sizeof(node_t));
    node->data = data;
    node->next = NULL;
    return node;
}

list_t* list_init(void) {
    list_t* list = malloc(sizeof(list_t));
    list->head = NULL;
    list->destroy = &list_destroy;
    list->to_string = &list_to_string;
    list->get_length = &list_get_length;
    list->get_node_at = &list_get_node_at;
    list->get_head = &list_get_head;
    list->get_tail = &list_get_tail;
    list->set_head = &list_set_head;
    list->set_tail = &list_set_tail;
    list->insert_at_beg = &list_insert_at_beg;
    list->insert_at_end = &list_insert_at_end;
    list->insert_at = &list_insert_at;
    list->delete_at_beg = &list_delete_at_beg;
    list->delete_at_end = &list_delete_at_end;
    return list;
}
