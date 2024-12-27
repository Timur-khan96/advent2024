#include <stdio.h>
#define BLINKS 75
#define MAX_VALUE 1000000

long memo[BLINKS + 1][MAX_VALUE + 1];

long process_stone(long value, int blink_count);
long split_left(long value);
long split_right(long value);
int num_digits(long value);

int main() {
    for (long i = 0; i <= BLINKS; i++) {
        for (int j = 0; j <= MAX_VALUE; j++) {
            memo[i][j] = -1;
        }
    }
    //0 44 175060 3442 593 54398 9 8101095

    long result = process_stone(0, BLINKS);
    result += process_stone(44, BLINKS);
    result += process_stone(175060, BLINKS);
    result += process_stone(3442, BLINKS);
    result += process_stone(593, BLINKS);
    result += process_stone(54398, BLINKS);
    result += process_stone(9, BLINKS);
    result += process_stone(8101095, BLINKS);

    printf("%ld\n", result);
}

long process_stone(long value, int blink_count) {
    if (blink_count == 0) return 1;
    long result = 1;
    if (value <= MAX_VALUE) {
        if (memo[blink_count][value] != -1) return memo[blink_count][value];
    }
    long origin_data[2] = {value, (long)blink_count};
    while (blink_count > 0) {
        if (value == 0) value++;
        else if (num_digits(value) % 2 == 0) {
            long tmp = value;
            value = split_left(value);
            result += process_stone(split_right(tmp), blink_count - 1);
        } else {
            value *= 2024;
        }
        blink_count--;
    }
    if (origin_data[0] <= MAX_VALUE) memo[origin_data[1]][origin_data[0]] = result;
    return result;
}

long split_left(long value) {
    int divisor = 1;
    int digits = num_digits(value);
    for (int i = 0; i < digits / 2; i++) {
        divisor *= 10;
    }
    return value / divisor;
}

long split_right(long value) {
    int divisor = 1;
    int digits = num_digits(value);
    for (int i = 0; i < digits / 2; i++) {
        divisor *= 10;
    }
    return value % divisor;
}

int num_digits(long value) {
    int count = 0;
    while (value > 0) {
        value /= 10;
        count++;
    }
    return count;
}