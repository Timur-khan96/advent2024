#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef LIST
#define LIST
typedef struct Node {
    long value;
    struct Node* next;
    struct Node* prev;
} Node;

Node* create_list(long value);
Node* create_node(long value);
Node* get_tail(Node* head);
void append(Node** head, long new_node_value);
void insert_after(Node* node, long new_node_value);
void free_list(Node* head);
long get_size(Node* head);
void print_list(Node* head);

#endif