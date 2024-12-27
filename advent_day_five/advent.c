#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define RULE_COUNT 1177

typedef struct Rule {
    int X;
    int Y;
} Rule;

int check_y_pos(int pages[], int page_count, Rule rule);
int check_x_pos(int pages[], int page_count, Rule rule);
int check_order(int pages[], int page_count, Rule rules[]);
void correct_order(int* pages, int page_count, Rule rules[]);


int main() {
    FILE* file_ptr = fopen("input.txt", "r");
    char* buffer = NULL;
    size_t buffer_size;
    ssize_t line_length;

    Rule rules[RULE_COUNT];
    int rule_count = 0;
    int rules_parsed = 0;

    int result_part_one = 0;
    int result_part_two = 0;

    while((line_length = getline(&buffer, &buffer_size, file_ptr)) != -1) {
        if (!rules_parsed) {
            if (sscanf(buffer, "%d|%d", &rules[rule_count].X, &rules[rule_count].Y) == EOF) {
                rules_parsed = 1;
            } else {
                rule_count++;
            }
        } else {
            int pages[100];
            int page_count = 0;
            char* token = strtok(buffer, ",");
            while (token != NULL) {
                pages[page_count++] = atoi(token);
                token = strtok(NULL, ",");
            }
            free(token);

            if (check_order(pages, page_count, rules)) {
                int middle_id = page_count / 2;
                result_part_one += pages[middle_id];
            } else {
                while (!check_order(pages, page_count, rules)) {
                    correct_order(pages, page_count, rules);
                }
                int middle_id = page_count / 2;
                result_part_two += pages[middle_id];
            }
        }
    }
    printf("advent day five part one result is %d\n", result_part_one);
    printf("advent day five part two result is %d\n", result_part_two);

    fclose(file_ptr);
    free(buffer);
}

int check_y_pos(int pages[], int page_count, Rule rule) {
    for (int i = 0; i < page_count; i++) {
        if (rule.Y == pages[i]) {
            return i;
        }
    }
    return -1;
}

int check_x_pos(int pages[], int page_count, Rule rule) {
    for (int i = 0; i < page_count; i++) {
        if (rule.X == pages[i]) {
            return i;
        }
    }
    return -1;
}

int check_order(int pages[], int page_count, Rule rules[]) {
    int is_order_correct = 1;

    for (int i = 0; i < page_count; i++) {
        for (int j = 0; j < RULE_COUNT; j++) {
            if (rules[j].X == pages[i]) {
                int y_pos = check_y_pos(pages, page_count, rules[j]);
                if (y_pos >= 0 && i > y_pos) {
                    is_order_correct = 0;
                    break;
                } 
            } else if (rules[j].Y == pages[i]) {
                int x_pos = check_x_pos(pages, page_count, rules[j]);
                if (x_pos >= 0 && i < x_pos) {
                    is_order_correct = 0;
                    break;
                }
            }
        }
        if (!is_order_correct) break;
    }
    return is_order_correct;
}

void correct_order(int* pages, int page_count, Rule rules[]) {
    int is_finished = 0;
    for (int i = 0; i < page_count; i++) {
        for (int j = 0; j < RULE_COUNT; j++) {
            if (rules[j].X == pages[i]) {
                int y_pos = check_y_pos(pages, page_count, rules[j]);
                if (y_pos >= 0 && i > y_pos) {
                    int tmp = pages[i];
                    pages[i] = pages[y_pos];
                    pages[y_pos] = tmp;
                    is_finished = 1;
                    break;
                }
            } else if (rules[j].Y == pages[i]) {
                int x_pos = check_x_pos(pages, page_count, rules[j]);
                if (x_pos >= 0 && i < x_pos) {
                    int tmp = pages[i];
                    pages[i] = pages[x_pos];
                    pages[x_pos] = tmp;
                    is_finished = 1;
                    break;
                }
            }
        }
        if (is_finished) break;
    }
}