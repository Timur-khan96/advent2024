#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#define HEIGHT 130
#define WIDTH 130
#define MAX_STEPS 4826

void rotate_guard(int* curr_dir) {
    if (curr_dir[0] == -1 && curr_dir[1] == 0) { //UP -> RIGHT
        curr_dir[0] = 0;
        curr_dir[1] = 1;
    } else if (curr_dir[0] == 0 && curr_dir[1] == 1) { //RIGHT -> DOWN
        curr_dir[0] = 1;
        curr_dir[1] = 0;
    } else if (curr_dir[0] == 1 && curr_dir[1] == 0) { //DOWN -> LEFT
        curr_dir[0] = 0;
        curr_dir[1] = -1;
    } else if (curr_dir[0] == 0 && curr_dir[1] == -1) { //LEFT -> UP
        curr_dir[0] = -1;
        curr_dir[1] = 0;
    } else {
        printf("Unknown direction");
        exit(1);
    }
}

void get_curr_pos(char (*map)[WIDTH], int* curr_pos) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map[y][x] == '^') {
                map[y][x] = 'X';
                curr_pos[0] = y;
                curr_pos[1] = x;
                return;
            }
        }
    }
    return;
}

int move_guard(char (*map)[WIDTH], int* curr_pos, int* curr_dir) {
    int next_y = curr_pos[0] + curr_dir[0];
    int next_x = curr_pos[1] + curr_dir[1];
    if (next_y < 0 || next_y >= HEIGHT || next_x < 0 || next_x >= WIDTH) {
        return 0;
    } else if (map[next_y][next_x] == '#') {
        rotate_guard(curr_dir);
        return move_guard(map, curr_pos, curr_dir);
    } else {
        curr_pos[0] = next_y;
        curr_pos[1] = next_x;
        return 1;
    }

}

int check_new_obstruction(char (*map)[WIDTH], int* curr_pos, int* curr_dir) {
    int step_count = 0; //to see if we are in the loop

    do {
        if (map[curr_pos[0]][curr_pos[1]] == 'X') {
            step_count++;
            if (step_count >= MAX_STEPS) {
                //printf("We are in the loop");
                return 1;
            }
            
        } else {
            map[curr_pos[0]][curr_pos[1]] = 'X';
            step_count = 0;
        }
    }
    while(move_guard(map, curr_pos, curr_dir));
    return 0;
}

int main() {
    FILE* file_ptr = fopen("input.txt", "r");
    char* buffer = NULL;
    size_t buffer_size;
    ssize_t line_length;

    char map[HEIGHT][WIDTH];
    int line_count = 0;
    
    while((line_length = getline(&buffer, &buffer_size, file_ptr)) != -1) {
        for (int i = 0; i < WIDTH; i++) {
            map[line_count][i] = buffer[i];
        }
        line_count++;
    }
    free(buffer);
    fclose(file_ptr);

    int curr_dir[2] = {-1, 0}; //Y|X;
    int curr_pos[2] = {-1, -1};
    get_curr_pos(map, curr_pos);

    int result = 0;
    int original_dir[2];
    int original_pos[2];
    char original_map[HEIGHT][WIDTH];
    memcpy(original_dir, curr_dir, sizeof(original_dir));
    memcpy(original_pos, curr_pos, sizeof(original_pos));
    memcpy(original_map, map, sizeof(original_map));

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map[y][x] == '#') continue;
            map[y][x] = '#';
            result += check_new_obstruction(map, curr_pos, curr_dir);
            memcpy(curr_dir, original_dir, sizeof(curr_dir));
            memcpy(curr_pos, original_pos, sizeof(curr_pos));
            memcpy(map, original_map, sizeof(map));
        }
    }
    printf("Advent day six part two result is %d", result);

}