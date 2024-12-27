#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "my_linked_list.h"
#define MAX_BLINKS 75
#define MAX_DIGITS 1024
#define MAX_VALUE 100000

long what_kind_of_bullshit_is_this(int help);
void blink(Node** head);

int main() {
    printf("Advent day eleven part one result is %ld\n", what_kind_of_bullshit_is_this(25)); //don't even try
    //part two is in another castle
}

long what_kind_of_bullshit_is_this(int help) {
    Node* head = create_list(0);
    append(&head, 44);
    append(&head, 175060);
    append(&head, 3442);
    append(&head, 593);
    append(&head, 54398);
    append(&head, 9);
    append(&head, 8101095);
    //0 44 175060 3442 593 54398 9 8101095

    for (int i = 0; i < help; i++) {
        // printf("Size: %ld | ", get_size(head));
        // print_list(head);
        printf("Blinked!\n");
        fflush(stdout);
        blink(&head);
    }
    long result = get_size(head);
    free_list(head);
    return result;
}

void blink(Node** head) {
    Node* current = get_tail(*head);
    while(current) {
        if (current->value == 0) current->value = 1;
        else {
            char buffer[1024];
            int digits_n = sprintf(buffer, "%ld", current->value);
            if (digits_n % 2 == 0) {
                int halved = digits_n / 2;
                char left_value[512] = {0}, right_value[512] = {0};
                memcpy(left_value, buffer, halved);
                memcpy(right_value, buffer + halved, halved);
                current->value = strtol(left_value, NULL, 10);
                insert_after(current, strtol(right_value, NULL, 10));
            } else {
                current->value *= 2024;
            }
            
        }
        current = current->prev;
    }
}

