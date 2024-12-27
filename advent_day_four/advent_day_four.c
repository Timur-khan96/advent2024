#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#define WIDTH 141
#define HEIGHT 140

int part_one(char (*wordsearch)[WIDTH]);
int check_xmas(char (*wordsearch)[WIDTH], int x, int y);
char check_dir(char (*wordsearch)[WIDTH], int x, int y, int dir[]);

int part_two(char (*wordsearch)[WIDTH]);
int check_cross(char (*wordsearch)[WIDTH], int x, int y);

int main() {
    char wordsearch[HEIGHT][WIDTH];

    FILE* file_ptr = fopen("input.txt", "r");
    char* buffer = NULL;
    size_t buffer_size;
    int row_count = 0;
    ssize_t line_length;
    while ((line_length = getline(&buffer, &buffer_size, file_ptr)) != -1) {
        for (ssize_t i = 0; i < line_length; i++) {
            wordsearch[row_count][i] = buffer[i];
            //printf("%c", wordsearch[row_count][i]);
        }
        row_count++;
    }
    fclose(file_ptr);
    free(buffer);

    printf("advent day four part one result is %d\n", part_one(wordsearch));
    printf("advent day four part two result is %d", part_two(wordsearch));
    
}

int part_two(char (*wordsearch)[WIDTH]) {
    int result = 0;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (wordsearch[y][x] == 'A') {
                result += check_cross(wordsearch, x, y);
            }
        }
    }
    return result;
}

int check_cross(char (*wordsearch)[WIDTH], int x, int y) {
    if (x == 0 || y == 0 || x + 1 == WIDTH || y + 1 == HEIGHT) return 0;
    int result = 0;
    if (wordsearch[y - 1][x - 1] == 'M' && wordsearch[y + 1][x + 1] == 'S') {
        if (wordsearch[y - 1][x + 1] == 'M' && wordsearch[y + 1][x - 1] == 'S') {
            result++;
        } else if (wordsearch[y - 1][x + 1] == 'S' && wordsearch[y + 1][x - 1] == 'M') {
            result++;
        }
    } else if (wordsearch[y - 1][x - 1] == 'S' && wordsearch[y + 1][x + 1] == 'M') {
        if (wordsearch[y - 1][x + 1] == 'M' && wordsearch[y + 1][x - 1] == 'S') {
            result++;
        } else if (wordsearch[y - 1][x + 1] == 'S' && wordsearch[y + 1][x - 1] == 'M') {
            result++;
        }
    }
    return result;
}

int part_one(char (*wordsearch)[WIDTH]) {
    int result = 0;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (wordsearch[y][x] == 'X') {
                result += check_xmas(wordsearch, x, y);
            }
        }
    }
    return result;
}

int check_xmas(char (*wordsearch)[WIDTH], int x, int y) {
    int curr_x = x;
    int curr_y = y;
    int result = 0;
    int dirs[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}; //y, x
    for (int i = 0; i < 8; i++) {
        x = curr_x;
        y = curr_y;
        if (check_dir(wordsearch, x, y, dirs[i]) == 'M') {
            x += dirs[i][1];
            y += dirs[i][0];
            if (check_dir(wordsearch, x, y, dirs[i]) == 'A') {
                x += dirs[i][1];
                y += dirs[i][0];
                if (check_dir(wordsearch, x, y, dirs[i]) == 'S') {
                    result += 1;
                }
            }
        }
        
    }
    return result;
}

char check_dir(char (*wordsearch)[WIDTH], int x, int y, int dir[]) {
    int curr_y = y + dir[0];
    int curr_x = x + dir[1];
    if (curr_y >= 0 && curr_y < HEIGHT && curr_x >= 0 && curr_x < WIDTH) {
        return wordsearch[curr_y][curr_x];
    } else {
        return ' ';
    }
}