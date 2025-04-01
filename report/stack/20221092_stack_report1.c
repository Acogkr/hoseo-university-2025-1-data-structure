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

void printStack(const Stack *stack) {
    printf("거꾸로 출력된 문자열 : ");
    for (int i = 0; i <= stack->top; ++i) {
        printf("%c", stack->arr[i]);
    }
    printf("\n");
}


int main() {
    Stack stack;
    char s[100];

    printf("문자열을 입력하세요 : ");

    init(&stack);
    scanf("%[^\n]s", s);

    for (int i = 0; i < MAX; ++i) {
        if (s[i] == '\0') {
            break;
        }
        push(&stack, s[i]);
    }

    printStack(&stack);
    return 0;
}