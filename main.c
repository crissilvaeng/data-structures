//
//  main.c
//  Singly Linked List
//
//  Created by Cristina Silva on 28/12/17.
//  Copyright © 2017 Cristina Silva. All rights reserved.
//

#include "definitions.h"
#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <mm_malloc.h>

static void assertm(bool assertion, char* message) {
    assert(assertion);
    printf("✔ %s\n", message);
}

static void list_init_should_alocate_memory(void) {
    // Arrange
    list_t* actual = NULL;
    // Act
    actual = list_init();
    // Assert
    assertm(actual != NULL, "List init should alocate memory.");
    // Clean
    actual->destroy(actual);
}

static void node_init_should_alocate_memory(void) {
    // Arrange
    node_t* actual = NULL;
    // Act
    actual = node_init(42);
    // Assert
    assertm(actual != NULL, "Node init should alocate memory.");
    // Clean
    free(actual);
}

static void list_get_length_should_return_the_length(void) {
    // Arrange
    list_t* list = list_init();
    int expected = 3;
    // Act
    list = list->insert_at_end(list, 42);
    list = list->insert_at_end(list, 42);
    list = list->insert_at_end(list, 42);
    int actual = list->get_length(list);
    // Assert
    assertm(expected == actual, "List get length should return the length.");
    // Clean
    list->destroy(list);
}

static void list_get_node_at_should_return_a_node_when_ask_for_a_first_exist_index() {
    // Arrange
    list_t* list = list_init();
    int expected = 1;
    // Act
    list = list->insert_at_end(list, 1);
    list = list->insert_at_end(list, 2);
    list = list->insert_at_end(list, 3);
    node_t* actual = list->get_node_at(list, 0);
    // Assert
    assertm(expected == actual->data, "List get node at should return a node when ask for a first exist index.");
    // Clean
    list->destroy(list);
}

static void list_get_node_at_should_return_a_node_when_ask_for_a_last_exist_index() {
    // Arrange
    list_t* list = list_init();
    int expected = 3;
    // Act
    list = list->insert_at_end(list, 1);
    list = list->insert_at_end(list, 2);
    list = list->insert_at_end(list, 3);
    node_t* actual = list->get_node_at(list, 2);
    // Assert
    assertm(expected == actual->data, "List get node at should return a node when ask for a last exist index.");
    // Clean
    list->destroy(list);
}

static void list_get_node_at_should_return_null_when_ask_for_inexist_index() {
    // Arrange
    list_t* list = list_init();
    node_t* expected = NULL;
    // Act
    list = list->insert_at_end(list, 1);
    list = list->insert_at_end(list, 2);
    list = list->insert_at_end(list, 3);
    node_t* actual = list->get_node_at(list, 3);
    // Assert
    assertm(expected == actual, "List get node at should return null when ask for a inexist index.");
    // Clean
    list->destroy(list);
}

static void list_get_head_should_return_first_element(void) {
    // Arrange
    list_t* list = list_init();
    int expected = 1;
    // Act
    list = list->insert_at_end(list, 1);
    node_t* actual = list->get_head(list);
    // Assert
    assertm(expected == actual->data, "List get head should return first element.");
    // Clean
    list->destroy(list);
}

static void list_get_head_should_return_null_if_head_unexist() {
    // Arrange
    list_t* list = list_init();
    node_t* expected = NULL;
    // Act
    node_t* actual = list->get_head(list);
    // Assert
    assertm(expected == actual, "List get head should return null if head unexist.");
    // Clean
    list->destroy(list);
}

static void list_get_tail_should_return_last_element(void) {
    // Arrange
    list_t* list = list_init();
    int expected = 2;
    // Act
    list = list->insert_at_end(list, 1);
    list = list->insert_at_end(list, 2);
    node_t* actual = list->get_tail(list);
    // Assert
    assertm(expected == actual->data, "List get tail should return last element.");
    // Clean
    list->destroy(list);
}

static void list_get_tail_should_return_null_if_tail_unexist() {
    // Arrange
    list_t* list = list_init();
    node_t* expected = NULL;
    // Act
    node_t* actual = list->get_tail(list);
    // Assert
    assertm(expected == actual, "List get tail should return null if tail unexist.");
    // Clean
    list->destroy(list);
}

static void list_get_tail_should_return_the_same_then_list_get_head_if_length_of_list_equals_one() {
    // Arrange
    list_t* list = list_init();
    int expected = 1;
    // Act
    list = list->insert_at_end(list, 1);
    node_t* head = list->get_head(list);
    node_t* tail = list->get_tail(list);
    int actual = list->get_length(list);
    // Assert
    assertm(head->data == tail->data && expected == actual, "List get tail should return the same then list get head if length of list equals one.");
    // Clean
    list->destroy(list);
}

static void list_set_head_should_set_a_head_in_a_empty_list() {
    // Arrange
    list_t* list = list_init();
    node_t* expected = node_init(42);
    // Act
    list = list->set_head(list, expected);
    node_t* actual = list->get_head(list);
    // Assert
    assertm(actual->data == expected->data, "List set head should set a head in a emptry list.");
    // Clean
    list->destroy(list);
}

static void list_set_head_should_set_a_new_head_for_a_list_with_the_previous_head_as_next() {
    // Arrange
    list_t* list = list_init();
    node_t* current = node_init(42);
    node_t* previous = NULL;
    // Act
    list = list->insert_at_end(list, 24);
    previous = list->get_head(list);
    list = list->set_head(list, current);
    node_t* actual = list->get_head(list);
    // Assert
    assertm(actual->data == current->data && previous->data == actual->next->data, "List set head should set a new head for a list with the previous head as next.");
    // Clean
    list->destroy(list);
}

int main(int argc, const char * argv[]) {
    list_init_should_alocate_memory();
    node_init_should_alocate_memory();
    list_get_length_should_return_the_length();
    list_get_node_at_should_return_a_node_when_ask_for_a_first_exist_index();
    list_get_node_at_should_return_a_node_when_ask_for_a_last_exist_index();
    list_get_node_at_should_return_null_when_ask_for_inexist_index();
    list_get_head_should_return_first_element();
    list_get_head_should_return_null_if_head_unexist();
    list_get_tail_should_return_last_element();
    list_get_tail_should_return_null_if_tail_unexist();
    list_get_tail_should_return_the_same_then_list_get_head_if_length_of_list_equals_one();
    list_set_head_should_set_a_head_in_a_empty_list();
    list_set_head_should_set_a_new_head_for_a_list_with_the_previous_head_as_next();
    printf("All tests passed!\n");
    return 0;
}
