#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#define ARR_MAX 1024

typedef struct Vector {
    int x;
    int y;
} Vector;

typedef struct Machine {
    Vector buttonA;
    Vector buttonB;
    Vector prize;
} Machine;

void press(Vector button, Vector* result) {
    result->x += button.x;
    result->y += button.y;
}

void unpress(Vector button, Vector* result) {
    result->x -= button.x;
    result->y -= button.y;
}

int has(int value, int arr[ARR_MAX], int arr_n) {
    if (!arr_n) return 0;
    for (int i = 0; i < arr_n; i++) {
        if (arr[i] == value) return 1;
    }
    return 0;
}

int find_lowest(int arr[ARR_MAX], int arr_n) {
    int value = arr[0];
    for (int i = 0; i < arr_n; i++) {
        if (arr[i] < value) value = arr[i];
    }
    return value;
}

int main() {
    FILE* file = fopen("input.txt", "r");
    char* buffer = NULL;
    size_t buffer_size = 0;
    ssize_t line_length = 0;

    size_t machines_size = 4;
    Machine* machines = (Machine*)malloc(machines_size * sizeof(Machine));
    int machine_n = 0;

    while((line_length = getline(&buffer, &buffer_size, file)) != -1) {
        if (line_length == 1) machine_n++;
        if (machine_n >= (int)machines_size) {
            machines_size *= 2;
            Machine* tmp = realloc(machines, machines_size * sizeof(Machine));
            if (tmp) machines = tmp;
            else {
                printf("Realloc error\n");
                fflush(stdout);
                free(machines);
                free(buffer);
                fclose(file);
                exit(1);
            }
        }
        //char buffer_2[100];
        sscanf(buffer, "Button A: X+%d, Y+%d", &machines[machine_n].buttonA.x, &machines[machine_n].buttonA.y);
        //getline(&buffer, &buffer_size, file);
        sscanf(buffer, "Button B: X+%d, Y+%d", &machines[machine_n].buttonB.x, &machines[machine_n].buttonB.y);
        sscanf(buffer, "Prize: X=%d, Y=%d", &machines[machine_n].prize.x, &machines[machine_n].prize.y);
    }
    machine_n++;
    free(buffer);
    fclose(file);

    // for (int i = 0; i < machine_n; i++) {
    //     printf("Machine #%d:\n", i);
    //     printf("Button A : x = +%d, y = +%d\n", machines[i].buttonA.x, machines[i].buttonA.y);
    //     printf("Button A : x = +%d, y = +%d\n", machines[i].buttonB.x, machines[i].buttonB.y);
    //     printf("Prize : x = %d, y = %d\n", machines[i].prize.x, machines[i].prize.y);
    // }

    long result = 0; //tokens spent

    for (int i = 0; i < (int)machine_n; i++) {
        Vector curr = {0};
        Vector target = machines[i].prize;
        int answers[ARR_MAX] = {0}, answers_count = 0, a_pressed = 0, b_pressed = 0;
        while (a_pressed < 100) {
            int answer_found = 0;
            while (b_pressed < 100) {
                press(machines[i].buttonB, &curr);
                b_pressed++;
                if (curr.x == target.x && curr.y == target.y) {
                    int value = a_pressed * 3 + b_pressed;
                    if (!has(value, answers, answers_count)) {
                        answer_found = 1;
                        answers[answers_count++] = value;
                        break;
                    }
                }
            }
            while (b_pressed != 0) {
                unpress(machines[i].buttonB, &curr);
                b_pressed--;
            }
            if (answer_found) continue;
            press(machines[i].buttonA, &curr);
            a_pressed++;
            if (curr.x == target.x && curr.y == target.y) {
                int value = a_pressed * 3 + b_pressed;
                if (!has(value, answers, answers_count)) {
                    answer_found = 1;
                    answers[answers_count++] = value;
                }
            }
        }
        if (answers_count) result += (long)find_lowest(answers, answers_count);
    }
    printf("Advent day thirteen part one result is %ld\n", result);
    free(machines);
    
}