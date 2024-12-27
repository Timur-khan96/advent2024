#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>

long calculate(long num_1, long num_2, char operation) {
    if (operation == '+') {
        return num_1 + num_2;
    } else if (operation == '*') {
        return num_1 * num_2;
    } else if (operation == '|') {
        char buffer[100];
        sprintf(buffer, "%ld%ld", num_1, num_2);
        return strtol(buffer, NULL, 10);
    } else {
        printf("Unknown operation");
        exit(1);
    }
}

void generateCombinations(char **combos, int n, int index, char *current, int *combo_index) {
    if (index == n) {
        memcpy(combos[*combo_index], current, n * sizeof(char));
        (*combo_index)++;
        return;
    }

    current[index] = '+';
    generateCombinations(combos, n, index + 1, current, combo_index);

    current[index] = '*';
    generateCombinations(combos, n, index + 1, current, combo_index);

    current[index] = '|'; // Adding the new operator for concatenation
    generateCombinations(combos, n, index + 1, current, combo_index);
}

char** generateAllOperatorCombinations(int n) {
    int combo_count = 1;
    for (int i = 0; i < n; i++) {
        combo_count *= 3; // 3^n combinations for three operators
    }

    char **combos = malloc(combo_count * sizeof(char *));
    for (int i = 0; i < combo_count; i++) {
        combos[i] = malloc(n * sizeof(char));
    }
    char *current = malloc(n * sizeof(char));
    int combo_index = 0;

    generateCombinations(combos, n, 0, current, &combo_index);

    free(current);
    return combos;
}

void freeCombinations(char **combos, int combo_count) {
    for (int i = 0; i < combo_count; i++) {
        free(combos[i]);
    }
    free(combos);
}

int is_equation_possible(int* operands, int operand_count, long equation_result) {
    int op_count = operand_count - 1;
    int combo_count = 1;
    for (int i = 0; i < op_count; i++) {
        combo_count *= 3; // 3^n combinations for three operators
    }
    char **combos = generateAllOperatorCombinations(op_count);

    for (int i = 0; i < combo_count; i++) {
        long curr_result = operands[0];
        for (int j = 0; j < op_count; j++) {
            curr_result = calculate(curr_result, (long)operands[j + 1], combos[i][j]);
        }
        if (curr_result == equation_result) {
            freeCombinations(combos, combo_count);
            return 1;
        }
    }
    freeCombinations(combos, combo_count);
    return 0;

}

int main() {
    FILE* file_ptr = fopen("input.txt", "r");
    char* buffer = NULL;
    size_t buffer_size;

    long result = 0;

    while(getline(&buffer, &buffer_size, file_ptr) != -1) {
        int operands[100];
        int operand_count = 0;
        char* token = strtok(buffer, ":");
        long equation_result = strtol(token, NULL, 10);
        token = strtok(NULL, " ");
        while(token != NULL) {
            operands[operand_count++] = atoi(token);

            token = strtok(NULL, " ");
        }
        if (is_equation_possible(operands, operand_count, equation_result)) {
            result += equation_result;
        }

    }
    fclose(file_ptr);
    free(buffer);
    printf("Advent day seven part two result is %ld", result);

}