#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 140
#define WIDTH 140

long calculate_price(int y, int x, char map[HEIGHT][WIDTH]);
void process_plot(int y, int x, char curr_char, int* area, int* perimeter, char map[HEIGHT][WIDTH]);

int main() {
    FILE* file_ptr = fopen("input.txt", "r");
    char* buffer = NULL;
    size_t buffer_size = 0;

    char map[HEIGHT][WIDTH];
    int y_count = 0;

    while(getline(&buffer, &buffer_size, file_ptr) != -1) {
        for (size_t i = 0; i < buffer_size; i++) {
            map[y_count][i] = buffer[i];
        }
        y_count++;
    }

    free(buffer);
    fclose(file_ptr);
    long result = 0;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map[y][x] != '0') {
                result += (long)calculate_price(y, x, map);
            }
        }
    }

    printf("Advent day twelve part one result is %ld\n", result);
}

long calculate_price(int y, int x, char map[HEIGHT][WIDTH]) {
    int area = 0, perimeter = 0;
    char curr_char = map[y][x];
    process_plot(y, x, curr_char, &area, &perimeter, map);
    printf("For char %c area is %d, perimeter is %d\n", curr_char, area, perimeter);

    for (int y_m = 0; y_m < HEIGHT; y_m++) {
        for (int x_m = 0; x_m < WIDTH; x_m++) {
            if (map[y_m][x_m] == '*') map[y_m][x_m] = '0';
        }
    }
    return area * perimeter;
}

void visualize(char map[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", map[y][x]);
        }
        printf("\n");
    }

}

void process_plot(int y, int x, char curr_char, int* area, int* perimeter, char map[HEIGHT][WIDTH]) {
    int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    map[y][x] = '*'; //currently processed
    //printf("Processing %c at (%d,%d), area is %d, perimeter is %d\n", curr_char, y, x, *area, *perimeter);
    //visualize(map);
    (*area)++;
    for (int i = 0; i < 4; i++) {
        int next_y = y + dirs[i][0];
        int next_x = x + dirs[i][1];

        if (next_y < 0 || next_y >= HEIGHT) {
            (*perimeter)++;
            if (next_x < 0 || next_x >= WIDTH) (*perimeter)++;
            continue;
        } else if (next_x < 0 || next_x >= WIDTH) {
            (*perimeter)++;
            if (next_y < 0 || next_y >= WIDTH) (*perimeter)++;
            continue;
        }

        char next_char = map[next_y][next_x];
        if (next_char == curr_char) {
            process_plot(next_y, next_x, curr_char, area, perimeter, map);
        } else if (next_char != '*') (*perimeter)++;
    }
}