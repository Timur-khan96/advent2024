#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define WIDTH 50
#define HEIGHT 50
#define LOCATIONS 2500 //50 * 50
#define ANTENNAS 100 //approximate for the number of similar antennas

int is_processed(char c, char processed_antennas[ANTENNAS]) {
    for (int i = 0; i < ANTENNAS; i++) {
        if (processed_antennas[i] == c) {
            return 1;
        }
    }
    return 0;
}

void get_curr_antennas_pos(char antenna, int pos_arr[ANTENNAS][2], int* antenna_count, char map[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map[y][x] == antenna) {
                pos_arr[*antenna_count][0] = y;
                pos_arr[*antenna_count][1] = x;
                (*antenna_count)++;
            }
        }
    }

}

int is_in_bounds(int y, int x) {
    return (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH);
}

int has_antinode(int antinode_pos[2], int antinodes_pos[LOCATIONS][2], int antinode_count) {
    if (antinode_count == 0) return 0;
    for (int i = 0; i < antinode_count; i++) {
        if (antinodes_pos[i][0] == antinode_pos[0] && antinodes_pos[i][1] == antinode_pos[1]) return 1;
    }
    return 0;
}

void get_curr_antinodes(int antennas_pos[ANTENNAS][2], int antennas_count, int antinodes_pos[LOCATIONS][2], int* antinode_count) {
    if (antennas_count <= 1) {
        printf("There are not enough antennas");
        return;
    }
    for (int i = 0; i < antennas_count; i++) {
        for (int j = 0; j < antennas_count; j++) {
            if (i == j) continue;
            int dist[2] = {antennas_pos[j][0] - antennas_pos[i][0], antennas_pos[j][1] - antennas_pos[i][1]};
            int rel_dist[2] = {dist[0], dist[1]};
            int next_pos[2] = {antennas_pos[i][0], antennas_pos[i][1]};
            do { //Here we add
                next_pos[0] += rel_dist[0];
                next_pos[1] += rel_dist[1];
                if (is_in_bounds(next_pos[0], next_pos[1])) {
                    if (!has_antinode(next_pos, antinodes_pos, *antinode_count)) {
                        antinodes_pos[*antinode_count][0] = next_pos[0];
                        antinodes_pos[*antinode_count][1] = next_pos[1];
                        (*antinode_count)++;
                    }
                }
            } while (is_in_bounds(next_pos[0], next_pos[1]));
            int neg_pos[2] = {antennas_pos[i][0], antennas_pos[i][1]};
            do { //Here we subtract
                neg_pos[0] -= rel_dist[0];
                neg_pos[1] -= rel_dist[1];
                if (is_in_bounds(neg_pos[0], neg_pos[1])) {
                    if (!has_antinode(neg_pos, antinodes_pos, *antinode_count)) {
                        antinodes_pos[*antinode_count][0] = neg_pos[0];
                        antinodes_pos[*antinode_count][1] = neg_pos[1];
                        (*antinode_count)++;
                    }
                }
            } while (is_in_bounds(neg_pos[0], neg_pos[1]));
        }
    }

}

int main() {
    FILE* file_ptr = fopen("input.txt", "r");
    char* buffer = NULL;
    size_t buffer_size;
    //GETTING MAP DATA
    char map[HEIGHT][WIDTH];
    int curr_y = 0;
    while(getline(&buffer, &buffer_size, file_ptr) != -1) {
        for (int i = 0; i < WIDTH; i++) {
            map[curr_y][i] = buffer[i];
        }
        curr_y++;
    }
    free(buffer);
    fclose(file_ptr);
    //PROCESSING MAP
    int antinodes_pos[LOCATIONS][2];
    int antinode_count = 0; // basically what we need to find
    char processed_antennas[ANTENNAS] = {0};
    int processed_count = 0;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            char c = map[y][x];
            if ((islower(c) || isupper(c) || isdigit(c)) && !is_processed(c, processed_antennas)) {
                processed_antennas[processed_count++] = c;
                int curr_antennas_pos[ANTENNAS][2]; 
                int curr_antennas_count = 0;
                get_curr_antennas_pos(c, curr_antennas_pos, &curr_antennas_count, map);
                get_curr_antinodes(curr_antennas_pos, curr_antennas_count, antinodes_pos, &antinode_count);
            }
        }
    }
    printf("Advent day eight part two result is %d", antinode_count);
}