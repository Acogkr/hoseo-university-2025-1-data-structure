#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 30  // 과제: 큐의 크기 30으로 변경

typedef struct {
    int data[SIZE];  // 고정된 크기의 배열
    int front;  // 큐의 첫 번째 요소 인덱스
    int rear;   // 큐의 마지막 요소 인덱스
} LinearQueue;

// 초기화 함수
void initQueue(LinearQueue *q) {
    q->front = 0;
    q->rear = -1;  // rear를 -1로 설정하여 첫 번째 삽입 시 0이 되도록 함
}

// 큐가 비어 있는지 확인
bool isEmpty(LinearQueue *q) {
    return q->rear < q->front;  // rear가 front보다 작으면 비어 있음
}

// 큐가 가득 찼는지 확인
bool isFull(LinearQueue *q) {
    return q->rear == SIZE - 1;  // rear가 배열 끝에 도달하면 가득 참
}

// 삽입 함수
bool enqueue(LinearQueue *q, int value) {
    if (isFull(q)) {
        printf("\n큐가 가득 찼습니다.\n");
        return false;
    }
    q->rear++;
    q->data[q->rear] = value;  // rear 위치에 데이터 추가
    return true;
}

// 삭제 함수
int dequeue(LinearQueue *q) {
    if (isEmpty(q)) {
        printf("dasd");
        printf("\n큐가 비어 있습니다.\n");
        return -1;  // 큐가 비어 있을 때 -1 반환
    }
    int value = q->data[q->front];
    q->front++;

    if (isEmpty(q)) { // 과제 부분 :: 큐가 비어 있으면 초기화
        initQueue(q);
    }

    return value;
}

int main() {
    LinearQueue q;
    initQueue(&q);

    while (1) {
        int index;
        printf("\n1. 삽입 2. 삭제 3. 현재 큐 상태 출력  4. 종료\n");
        printf("메뉴를 선택하세요 : ");

        scanf("%d", &index);

        switch (index) {
            case 1:
                printf("\n삽입할 값을 입력하세요 : ");
                int value;
                scanf("%d", &value);
                if (enqueue(&q, value)) {
                    printf("삽입 성공: %d\n", value);
                }
                break;
            case 2: { // C언어 컴파일 문제로 인한 임시 해결
                int deq = dequeue(&q);
                if (deq != -1) {
                    printf("\n삭제 성공: %d\n", deq);
                }
                break;
            }
            case 3:
                printf("\n현재 큐 상태 \n");
                printf("front: %d, rear: %d\n", q.front, q.rear);
                break;
            case 4:
                exit(1);
            default:
                printf("\n잘못된 입력입니다.\n");
                break;
        }
    }
}