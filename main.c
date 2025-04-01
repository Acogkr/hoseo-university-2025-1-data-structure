#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int top;
} Stack;

void init(Stack *stack) {
    stack->top = -1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int isFull(Stack *stack) {
    return stack->top == MAX - 1;
}

void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("꽉참 \n");
        return;
    }
    stack->arr[++stack->top] = value;
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("비었음 \n");
        return -1;
    }
    return stack->arr[stack->top--];
}

int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("비었음 \n");
        return -1;
    }
    return stack->arr[stack->top];
}

void printStack(const Stack *stack) { // 단지 값을 출력하는 것이기에 수정하지 못하도록 const를 붙임
    printf("Stack : ");
    for (int i = 0; i <= stack->top; ++i) {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}


int main() {
    Stack stack;
    init(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printStack(&stack);

    printf("pop : %d\n", pop(&stack));
    printStack(&stack);

    printf("peek : %d\n", peek(&stack));
    printStack(&stack);

    return 0;
}