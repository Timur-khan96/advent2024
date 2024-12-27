#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


int comp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

long advent_day_one_part_one() {
    FILE* file_ptr = fopen("advent_1.txt", "r");
    int arr_1[1000];
    int arr_2[1000];

    long total_distance = 0;
    for(int i = 0; i < 1000; i++) {
        fscanf(file_ptr, "%d   %d", &arr_1[i], &arr_2[i]);
    }
    qsort(arr_1, 1000, sizeof(int), comp);
    qsort(arr_2, 1000, sizeof(int), comp);
    for(int i = 0; i < 1000; i++) {
        total_distance += (long)abs(arr_1[i] - arr_2[i]);
        printf("%d: %d - %d = %ld\n", i, arr_1[i], arr_2[i], total_distance);
    }
    fclose(file_ptr);
    return total_distance;
}

long advent_day_one_part_two() {
    FILE* file_ptr = fopen("advent_1.txt", "r");
    int arr_1[1000];
    int arr_2[1000];

    long similarity_score = 0;
    for(int i = 0; i < 1000; i++) {
        fscanf(file_ptr, "%d   %d", &arr_1[i], &arr_2[i]);
    }
    int current_multiplier = 0;
    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < 1000; j++) {
            if (arr_1[i] == arr_2[j]) {
                current_multiplier++;
            }
        }
        similarity_score += arr_1[i] * current_multiplier;
        printf("%d: %d * %d = %ld\n", i, arr_1[i], current_multiplier, similarity_score);
        current_multiplier = 0;
    }
    fclose(file_ptr);
    return similarity_score;
}

int main() {
    printf("advent 1-1 result: %ld\n", advent_day_one_part_one());
    printf("advent 1-2 result: %ld\n", advent_day_one_part_two());
    
}