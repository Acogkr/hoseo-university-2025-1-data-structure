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

int getStudentScore(int scores[], int size, int studentNumber) {
    if (studentNumber >= 1 && studentNumber <= size) {
        return scores[studentNumber - 1];
    }
    return -1;
}

void printScore(const int option, int average, int scores[], int size) {
    if (option == 0) {
        for (int i = 0; i < size; ++i) {
            printf("학생 번호: %d, 점수: %d\n", i + 1, scores[i]);
        }
    } else if (option == 1) {
        for (int i = 0; i < size; ++i) {
            if (scores[i] >= average) {
                printf("학생 번호: %d, 점수: %d\n", i + 1, scores[i]);
            }
        }
    } else if (option == 2) {
        for (int i = 0; i < size; ++i) {
            if (scores[i] < average) {
                printf("학생 번호: %d, 점수: %d\n", i + 1, scores[i]);
            }
        }
    }
}

int main(void) {
    const int studentSize = 30;
    int score[studentSize];
    int studentIndex;

    srand(time(0));

    for (int i = 0; i < studentSize; ++i) {
        score[i] = rand() % 101;
    }

    const double average = calculateAverage(score, studentSize);
    printf("average: %.2f\n", average);

    printf("학생 번호를 입력하세요: ");
    scanf("%d", &studentIndex);

    int studentScore = getStudentScore(score, 30, studentIndex);
    if (studentScore == -1) {
        printf("학생 번호가 잘못되었습니다.\n");
    } else {
        printf("학생의 점수: %d\n", studentScore);
    }

    printScore(2, average, score, studentSize);
}