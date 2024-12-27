#include "my_linked_list.h"

Node* create_list(long value) {
    return create_node(value);
}
//prototype still needs researching
// Node* create_list(long count,...) {
//     va_list args;
//     va_start(args, count);
//     while(--count) {

//     }
//     va_end(args);
// }

Node* create_node(long value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void append(Node** head, long new_node_value) {
    Node* new_node = create_node(new_node_value);
    if (!(*head)) {
        *head = new_node;
        return;
    }
    Node* temp = *head;
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = new_node;
    new_node->prev = temp;
}

void insert_after(Node* node, long new_node_value) {
    if (!node) return;
    Node* new_node = create_node(new_node_value);
    new_node->next = node->next;
    new_node->prev = node;
    if (node->next) {
        node->next->prev = new_node;
    }
    node->next = new_node;
}

void free_list(Node* head) {
    if (!head) return;
    while (head) {
        Node* tmp = head;
        head = head-> next;
        free(tmp);
    }
}

void print_list(Node* head) {
    if (!head) return;
    while (head) {
        printf("%ld ", head->value);
        head = head->next;
    }
    printf("\n");
}

long get_size(Node* head) {
    if (!head) return 0;
    long result = 0;
    while(head) {
        result++;
        head = head->next;
    }
    return result;
}

Node* get_tail(Node* head) {
    if (!head) return 0;
    while(head->next) {
        head = head->next;
    }
    return head;
}

