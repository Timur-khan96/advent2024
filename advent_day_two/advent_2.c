#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int advent_day_two_part_one() {
    FILE* file_ptr = fopen("advent_2.txt", "r");
    char* buffer = NULL;
    size_t buffer_size = 0;
    ssize_t line_length = 0;
    int safe_reports_num = 0;

    while((line_length = getline(&buffer, &buffer_size, file_ptr)) != -1) {
        char* token;
        int is_current_report_safe = 1;
        int is_ascending = 0;
        int is_descending = 0;

        char* original_buffer = buffer;
        int prev_number = -1;

        while((token = strsep(&buffer, " ")) != NULL) {
            if (!is_current_report_safe) break;

            if (prev_number == -1) {
                prev_number = atoi(token);
                continue;
            } else {
                int curr_number = atoi(token);
                int diff = abs(prev_number - curr_number);
                if (diff < 1 || diff > 3) {
                    is_current_report_safe = 0;
                    break;
                }
                if (curr_number > prev_number) {
                    if (is_descending) {
                        is_current_report_safe = 0;
                        break;
                    } else {
                        is_ascending = 1;
                    }
                } else {
                    if (is_ascending) {
                        is_current_report_safe = 0;
                        break;
                    } else {
                        is_descending = 1;
                    }
                }
                prev_number = curr_number;
            }
        }
        buffer = original_buffer;
        safe_reports_num += is_current_report_safe;
    }
    free(buffer);

    fclose(file_ptr);
    return safe_reports_num;

}

int advent_day_two_part_two() {
    FILE* file_ptr = fopen("advent_2.txt", "r");
    char* buffer = NULL;
    size_t buffer_size = 0;
    ssize_t line_length = 0;

    int safe_reports_num = 0;
    int current_iteration = 0;
    while((line_length = getline(&buffer, &buffer_size, file_ptr)) != -1) {
        char* token;
        char* original_buffer = buffer; //strsep modifies the buffer

        int current_report[40];
        int current_report_length = 0;

        while((token = strsep(&buffer, " ")) != NULL) {
            current_report[current_report_length++] = atoi(token);
        }

        int is_current_report_safe = 1;
        int is_ascending = 0;
        int is_descending = 0;
        int is_removed = 0;
        int prev_number = -1;
        for(int i = 0; i < current_report_length; i++) {
            if (!is_current_report_safe) break;

            if (prev_number == -1) {
                prev_number = current_report[i];
                continue;
            } else {
                int curr_number = current_report[i];
                int diff = abs(prev_number - curr_number);
                if (diff < 1 || diff > 3) {
                    if (!is_removed) {
                        is_removed = 1;
                        continue;
                    } else {
                        is_current_report_safe = 0;
                        break;
                    }
                }
                if (curr_number > prev_number) {
                    if (is_descending) {
                        if (!is_removed) {
                            is_removed = 1;
                            continue;
                        } else {
                            is_current_report_safe = 0;
                            break;
                        }
                    } else {
                        is_ascending = 1;
                    }
                } else {
                    if (is_ascending) {
                        if (!is_removed) {
                            is_removed = 1;
                            continue;
                        } else {
                            is_current_report_safe = 0;
                            break;
                        }
                    } else {
                        is_descending = 1;
                    }
                }
                prev_number = curr_number;
            }

        }
        if (!is_current_report_safe) {
            //now we double check with nested loop
            for(int i = 0; i < current_report_length; i++) {
                is_current_report_safe = 1;
                is_ascending = 0;
                is_descending = 0;
                prev_number = -1;
                for(int j = 0; j < current_report_length; j++) {
                    if (i == j) continue;
                    if (!is_current_report_safe) break;

                    if (prev_number == -1) {
                        prev_number = current_report[j];
                        continue;
                    } else {
                        int curr_number = current_report[j];
                        int diff = abs(prev_number - curr_number);
                        if (diff < 1 || diff > 3) {
                            is_current_report_safe = 0;
                            break;
                        } else if (curr_number > prev_number) {
                            if (is_descending) {
                                is_current_report_safe = 0;
                                break;
                            } else {
                                is_ascending = 1;
                            }
                        } else {
                            if (is_ascending) {
                                is_current_report_safe = 0;
                                break;
                            } else {
                                is_descending = 1;
                            }
                        }
                        prev_number = curr_number;
                    }
                }
                if (is_current_report_safe) break;
            }
        }
        buffer = original_buffer;
        safe_reports_num += is_current_report_safe;
    }
    free(buffer);

    fclose(file_ptr);
    return safe_reports_num;
}




int main() {
    printf("advent 2-1 result: %d\n", advent_day_one_part_one());
    printf("advent 2-2 result: %d\n", advent_day_two_part_two());
    
}