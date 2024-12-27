#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HEIGHT 140
#define WIDTH 140 

long calculate_price(int y, int x, char map[HEIGHT][WIDTH]);
void get_area(int y, int x, char curr_char, int* area, char map[HEIGHT][WIDTH]);
int get_sides(char map[HEIGHT][WIDTH]);

int main() {
    FILE* file_ptr = fopen("input.txt", "r");
    char* buffer = NULL;
    size_t buffer_size = 0;

    char map[HEIGHT][WIDTH];
    int y_count = 0;

    while(getline(&buffer, &buffer_size, file_ptr) != -1 && y_count < HEIGHT) {
        for (size_t i = 0; i < WIDTH; i++) {
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

    printf("Advent day twelve part two result is %ld\n", result);
}

long calculate_price(int y, int x, char map[HEIGHT][WIDTH]) {
    int area = 0;
    char curr_char = map[y][x];
    get_area(y, x, curr_char, &area, map);
    int sides_n = get_sides(map);
    for (int y_m = 0; y_m < HEIGHT; y_m++) {
        for (int x_m = 0; x_m < WIDTH; x_m++) {
            if (map[y_m][x_m] == '*') map[y_m][x_m] = '0';
        }
    }
    return area * sides_n;
}

void get_area(int y, int x, char curr_char, int* area, char map[HEIGHT][WIDTH]) {
    int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    (*area)++;
    map[y][x] = '*';
    for (int i = 0; i < 4; i++) {
        int next_y = y + dirs[i][0];
        int next_x = x + dirs[i][1];

        if (next_y < 0 || next_y >= HEIGHT || next_x < 0 || next_x >= WIDTH) continue;
        char next_char = map[next_y][next_x];
        if (next_char == curr_char) get_area(next_y, next_x, curr_char, area, map);
    }
}

int match_pattern(const int *square, const int *pattern, int size) {
    for (int i = 0; i < size; i++) {
        if (square[i] != pattern[i]) {
            return 0;
        }
    }
    return 1;
}

int check_one_corner_patterns(const int square[4]) {
    const int one_corner_patterns[8][4] = {
        {0, 0, 0, 1}, {0, 0, 1, 0}, {0, 1, 0, 0}, {1, 0, 0, 0},
        {1, 1, 1, 0}, {1, 1, 0, 1}, {1, 0, 1, 1}, {0, 1, 1, 1}
    };
    for (int i = 0; i < 8; i++) {
        if (match_pattern(square, one_corner_patterns[i], 4)) {
            return 1;
        }
    }
    return 0;
}

int check_two_corner_patterns(const int square[4]) {
    const int two_corner_patterns[2][4] = {
        {1, 0, 0, 1}, {0, 1, 1, 0}
    };
    for (int i = 0; i < 2; i++) {
        if (match_pattern(square, two_corner_patterns[i], 4)) {
            return 1;
        }
    }
    return 0;
}

int get_sides(char map[HEIGHT][WIDTH]) {
    int result = 0;
    for (int iy = -1; iy + 1 <= HEIGHT; iy++) {
        for (int jx = -1; jx + 1 <= WIDTH; jx++) {
            int square[4] = {0, 0, 0, 0}; //top-left, top-right, bottom-left, bottom-right
            if (iy == -1 || iy+1 == HEIGHT || jx == -1 || jx+1 == WIDTH) {
                square[0] = iy == -1 ? 1 : jx == -1 ? 1 : map[iy][jx] == '*' ? 0 : 1;
                square[1] = iy == -1 ? 1 : jx+1 == WIDTH ? 1 : map[iy][jx+1] == '*' ? 0 : 1;
                square[2] = iy+1 == HEIGHT ? 1 : jx == -1 ? 1 : map[iy+1][jx] == '*' ? 0 : 1;
                square[3] = iy+1 == HEIGHT ? 1 : jx+1 == WIDTH ? 1 : map[iy+1][jx+1] == '*' ? 0 : 1;
            } else {
                square[0] = map[iy][jx] == '*' ? 0 : 1;
                square[1] = map[iy][jx+1] == '*' ? 0 : 1;
                square[2] = map[iy+1][jx] == '*' ? 0 : 1;
                square[3] = map[iy+1][jx+1] == '*' ? 0 : 1;
            }

            if (square[0] == square[1] && square[1] == square[2] && square[2] == square[3]) continue;
            if (check_one_corner_patterns(square)) {
                result++;
            } else if (check_two_corner_patterns(square)) {
                result += 2;
            }
        }
    }
    return result;
}