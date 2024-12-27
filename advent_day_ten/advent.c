#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 60
#define WIDTH 60
#define LOCATIONS 3600 //Just approximate number of trail ends on the map

int part_one();
void get_trail_score(int curr_pos[2], int curr_height, int map[HEIGHT][WIDTH], int* curr_score, 
                    int processed[LOCATIONS][2], int* processed_count);
int is_processed(int pos[2], int processed[LOCATIONS][2], int processed_count);

int part_two();
void get_trail_raiting(int curr_pos[2], int curr_height, int map[HEIGHT][WIDTH], int* curr_score, 
                    int processed[LOCATIONS][2], int* processed_count, int* is_unique);
int process_location(int pos[2], int processed[LOCATIONS][2], int* processed_count);

int main() {
    printf("Advent day 10 part one result is %d\n", part_one());
    printf("Advent day 10 part two result is %d", part_two());
    
}

int part_one() {
    FILE* file_ptr = fopen("input.txt", "r");
    char* buffer = NULL;
    size_t buffer_size;

    int map[HEIGHT][WIDTH];
    int line_count = 0;
    
    while(getline(&buffer, &buffer_size, file_ptr) != -1) {
        if (line_count > HEIGHT) break;
        for (int i = 0; i < WIDTH; i++) {
            map[line_count][i] = (int)buffer[i] - 48;
        }
        line_count++;
    }
    int result = 0;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map[y][x] == 0) {
                int curr_pos[2] = {y, x};
                int processed[LOCATIONS][2];
                int processed_count = 0;
                get_trail_score(curr_pos, 0, map, &result, processed, &processed_count);
            }
        }
    }
    fclose(file_ptr);
    free(buffer);
    return result;
}

void get_trail_score(int curr_pos[2], int curr_height, int map[HEIGHT][WIDTH], int* curr_score, 
                    int processed[LOCATIONS][2], int* processed_count) {
    int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    for (int i = 0; i < 4; i++) {
        int new_pos[2] = {curr_pos[0] + dirs[i][0], curr_pos[1] + dirs[i][1]};
        if (new_pos[0] >= 0 && new_pos[0] < HEIGHT && new_pos[1] >= 0 && new_pos[1] < WIDTH) {
            int new_height = map[new_pos[0]][new_pos[1]];
            if (new_height == 9 && curr_height == 8) {
                if (!is_processed(new_pos, processed, (*processed_count))) {
                    (*curr_score)++;
                    processed[(*processed_count)][0] = new_pos[0];
                    processed[(*processed_count)][1] = new_pos[1];
                    (*processed_count)++;
                }
            } else if (new_height - curr_height == 1) {
                get_trail_score(new_pos, new_height, map, curr_score, processed, processed_count);
            }
        }
    }
}

int is_processed(int pos[2], int processed[LOCATIONS][2], int processed_count) {
    if (processed_count == 0) return 0;
    for (int i = 0; i < processed_count; i++) {
        if (processed[i][0] == pos [0] && processed[i][1] == pos [1]) return 1;
    }
    return 0;
}

int part_two() {
    FILE* file_ptr = fopen("input.txt", "r");
    char* buffer = NULL;
    size_t buffer_size;

    int map[HEIGHT][WIDTH];
    int line_count = 0;
    
    while(getline(&buffer, &buffer_size, file_ptr) != -1) {
        if (line_count > HEIGHT) break;
        for (int i = 0; i < WIDTH; i++) {
            map[line_count][i] = (int)buffer[i] - 48;
        }
        line_count++;
    }
    int result = 0;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map[y][x] == 0) {
                int curr_pos[2] = {y, x};
                int processed[LOCATIONS][2];
                int processed_count = 0;
                int is_trail_unique = 1;
                get_trail_raiting(curr_pos, 0, map, &result, processed, &processed_count, &is_trail_unique);
            }
        }
    }
    fclose(file_ptr);
    free(buffer);
    return result;
}

void get_trail_raiting(int curr_pos[2], int curr_height, int map[HEIGHT][WIDTH], int* curr_score, 
                    int processed[LOCATIONS][2], int* processed_count, int* is_unique) {
    int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    for (int i = 0; i < 4; i++) {
        int new_pos[2] = {curr_pos[0] + dirs[i][0], curr_pos[1] + dirs[i][1]};
        if (new_pos[0] >= 0 && new_pos[0] < HEIGHT && new_pos[1] >= 0 && new_pos[1] < WIDTH) {
            int new_height = map[new_pos[0]][new_pos[1]];
            if (new_height == 9 && curr_height == 8) {
                if (is_unique) {
                    (*curr_score)++;
                }
            } else if (new_height - curr_height == 1) {
                (*is_unique) = process_location(new_pos, processed, processed_count);
                get_trail_raiting(new_pos, new_height, map, curr_score, processed, processed_count, is_unique);
            }
        }
    }
}

int process_location(int pos[2], int processed[LOCATIONS][2], int* processed_count) {
    for (int i = 0; i < (*processed_count); i++) {
        if (processed[i][0] == pos [0] && processed[i][1] == pos [1]) return 0;
    }
    processed[(*processed_count)][0] = pos[0];
    processed[(*processed_count)][1] = pos[1];
    (*processed_count)++;
    return 1;
}