#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

long advent_day_three_part_one() {
    //this one uses grep results as it is easy regex
    FILE* file_ptr = fopen("grep_result.txt", "r");
    char* buffer = NULL;
    size_t buffer_size = 0;

    long result = 0;

    while(getline(&buffer, &buffer_size, file_ptr) != -1) {
        int num_1;
        int num_2;
        sscanf(buffer, "mul(%d,%d)", &num_1, &num_2);
        result += (long)(num_1 * num_2);
    }
    return result;
}

int* get_pattern_all_pos(regex_t pattern, char* file_buffer, size_t* match_count) {
    char* search_ptr = file_buffer;
    size_t result_size = 4;
    int* result = (int*)malloc(result_size * sizeof(int));

    size_t nmatch = 1;
    regmatch_t pmatch[1];
    int rc;

    while((rc = regexec(&pattern, search_ptr, nmatch, pmatch, 0)) == 0) {
        result[(*match_count)++] = pmatch[0].rm_so + (search_ptr - file_buffer);
        if (*match_count >= result_size) {
            result_size *= 2;
            result = (int*)realloc(result, result_size * sizeof(int));
            if (result == NULL) {
                printf("Error at reallocating memory");
                exit(0);
            }
        }
        search_ptr += pmatch[0].rm_eo;
    }

    result = (int*)realloc(result, (*match_count) * sizeof(int));
    if (result == NULL) {
        printf("Error at reallocating memory");
        exit(0);
    }
    return result;
}

int* get_product_arr() {
    FILE* file_ptr2 = fopen("grep_result.txt", "r");
    char* buffer = NULL;
    size_t buffer_size = 0;

    int* product_results = (int*)malloc(695 * sizeof(int));
    int counter = 0;

    while(getline(&buffer, &buffer_size, file_ptr2) != -1) {
        int num_1;
        int num_2;
        sscanf(buffer, "mul(%d,%d)", &num_1, &num_2);
        product_results[counter++] = num_1 * num_2;
    }

    free(buffer);
    fclose(file_ptr2);
    return product_results;
}

long advent_day_three_part_two() {
        FILE* file_ptr = fopen("advent_3.txt", "r");
    size_t file_buffer_size = 1024;
    char* file_buffer = (char*)malloc(file_buffer_size * sizeof(char));

    size_t file_buffer_length = 0;
    char ch;
    while((ch = fgetc(file_ptr)) != EOF) {
        file_buffer[file_buffer_length++] = ch;

        if (file_buffer_length >= file_buffer_size) {
            file_buffer_size *= 2;
            file_buffer = (char*)realloc(file_buffer, file_buffer_size);
            if (file_buffer == NULL) {
                printf("Failed to reallocate memory");
                free(file_buffer);
                fclose(file_ptr);
                exit(0);
            }
        }
    }
    file_buffer[file_buffer_length] = '\0';

    regex_t mul_pattern, do_pattern, dont_pattern;

    int rc;
    if (0 != (rc = regcomp(&mul_pattern, "mul([0-9]*,[0-9]*)", 0))) {
        printf("regcomp() failed, returning nonzero (%d)\n", rc);
        exit(EXIT_FAILURE);
    }
    if (0 != (rc = regcomp(&do_pattern, "do()", 0))) {
        printf("regcomp() failed, returning nonzero (%d)\n", rc);
        exit(EXIT_FAILURE);
    }
    if (0 != (rc = regcomp(&dont_pattern, "don't()", 0))) {
        printf("regcomp() failed, returning nonzero (%d)\n", rc);
        exit(EXIT_FAILURE);
    }

    size_t do_pos_arr_size = 0;
    int* do_pos_arr = get_pattern_all_pos(do_pattern, file_buffer, &do_pos_arr_size);

    size_t dont_pos_arr_size = 0;
    int* dont_pos_arr = get_pattern_all_pos(dont_pattern, file_buffer, &dont_pos_arr_size);

    size_t mul_pos_arr_size = 0;
    int* mul_pos_arr = get_pattern_all_pos(mul_pattern, file_buffer, &mul_pos_arr_size);

    int* product_results = get_product_arr();
    long result = 0;

    size_t do_count = 0;
    int next_do_pos = do_pos_arr[do_count];

    size_t dont_count = 0;
    int next_dont_pos = dont_pos_arr[dont_count];
    int is_mul_enabled = 1; //enabled by default

    for(size_t i = 0; i < mul_pos_arr_size; i++) {
        if (next_dont_pos < mul_pos_arr[i]) {
            if (next_do_pos < mul_pos_arr[i] && next_do_pos > next_dont_pos) {
                is_mul_enabled = 1;
                while(next_dont_pos < next_do_pos) {
                    if (dont_count >= dont_pos_arr_size) break;
                    next_dont_pos = dont_pos_arr[dont_count++];
                }
                if (next_dont_pos < mul_pos_arr[i] && next_dont_pos > next_do_pos) {
                    is_mul_enabled = 0;
                }
            } else {
                is_mul_enabled = 0;
                while(next_do_pos < next_dont_pos) {
                    if (do_count >= do_pos_arr_size) break;
                    next_do_pos = do_pos_arr[do_count++];
                }
                if (next_do_pos < mul_pos_arr[i] && next_do_pos > next_dont_pos) {
                    is_mul_enabled = 1;
                }
            }
        } else if (!is_mul_enabled) {
            if (next_do_pos < next_dont_pos && next_do_pos < mul_pos_arr[i]) {
                is_mul_enabled = 1;
            }
        }

        if (is_mul_enabled) {
            result += (long)product_results[i];
        }
    }


    regfree(&mul_pattern);
    regfree(&do_pattern);
    regfree(&dont_pattern);
    free(do_pos_arr);
    free(dont_pos_arr);
    free(mul_pos_arr);
    free(product_results);
    free(file_buffer);
    fclose(file_ptr);

    return result;
}

int main() {
    printf("advent 3-1 result: %ld\n", advent_day_three_part_one());
    printf("advent 3-2 result: %ld\n", advent_day_three_part_two());

}