#include <stdio.h>

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
        return -1;
    }
    return stack->arr[stack->top];
}

void printStack(const Stack *stack) { // 단지 값을 출력하는 것이기에 수정하지 못하도록 const를 붙임
    printf("Stack : ");
    for (int i = 0; i <= stack->top; ++i) {
        printf("%c ", stack->arr[i]);
    }
    printf("\n");
}


int main() {
    Stack brackets;
    char s[MAX];

    printf("문자열을 입력하세요 : ");

    init(&brackets);
    scanf("%[^\n]s", s);

    for (int i = 0; i < MAX; ++i) {
        const char c = s[i];

        if (c == '(' || c == '[' || c == '{') {
            push(&brackets, c);
        }

        if (c == ')' || c == ']' || c == '}') {
            char p = peek(&brackets);

            if (p == -1) {
                printf("유효하지 않은 괄호 \n");
                return 0;
            }

            if (p == '(' && c == ')') {
                pop(&brackets);
            }
            else if (p == '[' && c == ']') {
                pop(&brackets);
            }
            else if (p == '{' && c == '}') {
                pop(&brackets);
            }
        }
    }

    if (isEmpty(&brackets)) {
        printf("유효한 괄호 \n");
    } else {
        printf("유효하지 않은 괄호 \n");
    }

    return 0;
}