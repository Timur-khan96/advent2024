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

    int curr_file_searcher = curr_visual_pos - 1;
    int is_finished = 0;
    while(curr_file_searcher >= 0) {
        curr_file_id = -1;
        while(curr_file_id == -1) {
            if (visual_buffer[curr_file_searcher] == -1) {
                while(visual_buffer[curr_file_searcher] == -1) {
                    curr_file_searcher--;
                    if (curr_file_searcher < 0) {
                        is_finished = 1;
                        break;
                    }
                }
            }
            if (curr_file_searcher < 0) break;
            curr_file_id = visual_buffer[curr_file_searcher];
        }
        if (is_finished) break;

        size_t curr_file_size = 0;
        while(visual_buffer[curr_file_searcher] == curr_file_id) {
            curr_file_searcher--;
            if (curr_file_searcher < 0) break;
            curr_file_size++;
        }
        size_t curr_space_searcher = 0;
        size_t curr_space_size = 0;
        while(curr_space_searcher < curr_visual_pos) {
            if (visual_buffer[curr_space_searcher] == -1) {
                curr_space_size++;
            } else {
                curr_space_size = 0;
            }
            if (curr_space_size == curr_file_size) break;
            curr_space_searcher++;
        }
        if (curr_space_size == 0 || curr_space_searcher >= curr_visual_pos) continue;
        if ((int)curr_space_searcher > curr_file_searcher) continue;
        curr_file_searcher++; //because it went to the next memory slot previuosly
        
        while (curr_space_size > 0) {
            visual_buffer[curr_space_searcher] = visual_buffer[curr_file_searcher];
            visual_buffer[curr_file_searcher] = -1;
            curr_space_searcher--;
            curr_file_searcher++;
            curr_space_size--;
        }
        curr_file_searcher--;
    }
    
    long result = 0;
    for(size_t i = 0; i < curr_visual_pos; i++) {
        if (visual_buffer[i] == -1) continue;
        result += (long)i * visual_buffer[i];
    }
    printf("Advent day nine part two result is %ld", result);
    free(visual_buffer);
}