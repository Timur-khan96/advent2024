#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* file_ptr = fopen("input.txt", "r");
    if (!file_ptr) {
        printf("Error while opening the file");
    }
    int ch;

    size_t visual_size = 1024;
    int* visual_buffer = malloc(visual_size * sizeof(int));

    size_t curr_visual_pos = 0;

    int is_file = 1;
    int curr_file_id = 0;
    while((ch = fgetc(file_ptr)) != EOF) {
        if (ch == '\n') continue;
        if (is_file) {
            is_file = 0;
            int curr_file_length = ch - 48;

            if (curr_visual_pos + (size_t)curr_file_length >= visual_size) {
                visual_size *= 2;
                int* tmp = realloc(visual_buffer, visual_size * sizeof(int));
                if (tmp) {
                    visual_buffer = tmp;
                } else {
                    printf("Error during reallocation");
                    free(visual_buffer);
                    exit(1);
                }
            }

            for (int i = 0; i < curr_file_length; i++) {
                visual_buffer[curr_visual_pos++] = curr_file_id;
            }
            curr_file_id++;
        } else { //not a file therefore free disk-space
            is_file = 1;
            int curr_free_space = ch - 48;

            if (curr_visual_pos + (size_t)curr_free_space >= visual_size) {
                visual_size *= 2;
                int* tmp = realloc(visual_buffer, visual_size * sizeof(int));
                if (tmp) {
                    visual_buffer = tmp;
                } else {
                    printf("Error during reallocation");
                    free(visual_buffer);
                    exit(1);
                }
            }

            for (int i = 0; i < curr_free_space; i++) {
                visual_buffer[curr_visual_pos++] = -1;
            }
        } 
    }

    fclose(file_ptr);

    // for (size_t i = 0; i < curr_visual_pos; i++) {
    //     if (visual_buffer[i] == -1) {
    //         printf(".");
    //     } else {
    //         printf("%d", visual_buffer[i]);
    //     }
    // }
    // printf("\n");
    size_t curr_file_searcher = curr_visual_pos - 1;
    int is_finished = 0;
    for(size_t i = 0; i < curr_visual_pos; i++) {
        if (is_finished) break;
        if (visual_buffer[i] != -1) continue;
        if (visual_buffer[curr_file_searcher] == -1) {
            while(visual_buffer[curr_file_searcher] == -1) curr_file_searcher--;
        }
        visual_buffer[i] = visual_buffer[curr_file_searcher];
        visual_buffer[curr_file_searcher] = -1;
        curr_file_searcher = curr_visual_pos - 1;

        size_t is_finished_check = 0;
        while(visual_buffer[is_finished_check] != -1) is_finished_check++;
        while(is_finished_check < curr_visual_pos) {
            is_finished = 1;
            if (visual_buffer[is_finished_check] != -1) {
                is_finished = 0;
                break;
            }
            is_finished_check++;
        }

        // for (size_t j = 0; j < curr_visual_pos; j++) {
        //     if (visual_buffer[j] == -1) {
        //         printf(".");
        //     } else {
        //         printf("%d", visual_buffer[j]);
        //     }
        // }
        // printf("\n");
    }
    long result = 0;
    curr_file_searcher = 0;
    while(visual_buffer[curr_file_searcher] != -1) {
        result += (long)curr_file_searcher * visual_buffer[curr_file_searcher];
        curr_file_searcher++;
    }
    printf("%ld", result);
    free(visual_buffer);
}