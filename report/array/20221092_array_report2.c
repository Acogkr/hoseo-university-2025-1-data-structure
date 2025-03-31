#include <stdio.h>
#include <stdlib.h>

int* resize(int *arr, int* size, const int afterSize) {
    int* newArr = (int*) malloc(afterSize * sizeof(int));
    for (int i = 0; i < *size; ++i) {
        newArr[i] = arr[i];
    }
    *size = afterSize;
    free(arr);
    return newArr;
}

int* addStudent(int* arr, int* size, int count, int score) {
    arr = resize(arr, size, *size + count);
    for (int i = *size - count; i < *size; ++i) {
        arr[i] = score;
    }
    return arr;
}

int* removeStudent(int* arr, int* size, int index) {
    if (index < 0 || index >= *size) {
        return arr;
    }

    for (int i = index; i < *size - 1; ++i) {
        arr[i] = arr[i + 1];
    }

    arr = resize(arr, size, *size - 1);
    return arr;
}

int main() {
    int size = 5;
    int* arr = (int*) malloc(size * sizeof(int));

    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }

    printf("1 : ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    arr = addStudent(arr, &size, 2, 20);
    printf("2 : ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    arr = removeStudent(arr, &size, 2);
    printf("3 : ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}