#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double calculateAverage(const int score[], const int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += score[i];
    }
    return (double) sum / size;
}


int main(void) {
    int score[10];

    srand(time(0));

    for (int i = 0; i < 10; ++i) {
        score[i] = rand() % 101;

    }

    printf("average: %.2f\n", calculateAverage(score, 10));
}
