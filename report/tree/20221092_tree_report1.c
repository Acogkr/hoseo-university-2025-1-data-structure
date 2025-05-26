#include <stdio.h>
#include <stdlib.h>

// 이진 트리 노드를 정의하는 구조체
typedef struct TreeNode {
    int data;                      // 노드에 저장할 데이터
    struct TreeNode* left;        // 왼쪽 자식 노드를 가리키는 포인터
    struct TreeNode* right;       // 오른쪽 자식 노드를 가리키는 포인터
} TreeNode;

// 노드를 생성하고 초기화하는 함수
TreeNode* createNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        printf("메모리 할당 오류\n");
        exit(1);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void preorder(TreeNode* node) {
    if (node == NULL) return;

    printf("%d ", node->data);      // 1. 루트 방문
    preorder(node->left);           // 2. 왼쪽 서브트리 순회
    preorder(node->right);          // 3. 오른쪽 서브트리 순회
}

void inorder(TreeNode* node) {
    if (node == NULL) return;

    inorder(node->left);            // 1. 왼쪽 서브트리 순회
    printf("%d ", node->data);     // 2. 루트 방문
    inorder(node->right);          // 3. 오른쪽 서브트리 순회
}

void postorder(TreeNode* node) {
    if (node == NULL) return;

    postorder(node->left);         // 1. 왼쪽 서브트리 순회
    postorder(node->right);        // 2. 오른쪽 서브트리 순회
    printf("%d ", node->data);     // 3. 루트 방문
}

void freeTree(TreeNode* node) {
    if (node == NULL) return;

    freeTree(node->left);   // 왼쪽 서브트리 먼저 해제
    freeTree(node->right);  // 오른쪽 서브트리 해제
    free(node);             // 현재 노드 해제
}

int getHeight(TreeNode* node) {
    if (node == NULL) return -1;  // NULL 자식은 간선 없음 → 높이 -1

    int leftHeight = getHeight(node->left);   // 왼쪽 서브트리의 높이
    int rightHeight = getHeight(node->right); // 오른쪽 서브트리의 높이

    if(leftHeight > rightHeight) return leftHeight + 1;
    else return rightHeight + 1;
}

int countNodes(TreeNode* node) {
    if (node == NULL) return 0;

    return 1 + countNodes(node->left) + countNodes(node->right);
}

int countLeaves(TreeNode* node) {
    if (node == NULL) return 0;

    if (node->left == NULL && node->right == NULL)
        return 1;  // 리프 노드일 경우

    return countLeaves(node->left) + countLeaves(node->right);
}

// 과제 :
int getSum(TreeNode* node) {
    if (node == NULL) return 0;

    return node->data + getSum(node->left) + getSum(node->right);
}

// 과제 :
int getMax(TreeNode* node) {
    if (node == NULL) return -1;  // 트리가 비어있을 경우

    int leftMax = getMax(node->left);
    int rightMax = getMax(node->right);

    int max = node->data;
    if (leftMax > max) max = leftMax;
    if (rightMax > max) max = rightMax;

    return max;
}

// 과제 :
void searchRange(TreeNode* node, int min, int max) {
    if (node == NULL) return;

    if (node->data >= min && node->data <= max) {
        printf("%d ", node->data);
    }

    searchRange(node->left, min, max);
    searchRange(node->right, min, max);
}

int main() {
    // 트리 구성
    TreeNode* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(20);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->left = createNode(15);
    root->right->right = createNode(25);

    // 순회 출력
    printf("전위 순회: ");
    preorder(root);
    printf("\n");

    printf("중위 순회: ");
    inorder(root);
    printf("\n");

    printf("후위 순회: ");
    postorder(root);
    printf("\n");

    // 분석 출력
    printf("트리 높이: %d\n", getHeight(root));
    printf("전체 노드 수: %d\n", countNodes(root));
    printf("리프 노드 수: %d\n", countLeaves(root));

    printf("노드 값 총합: %d\n", getSum(root));  // 함수 작성
    printf("최댓값: %d\n", getMax(root));       // 함수 작성
    printf("\n");

    // 범위 탐색
    printf("값이 6 이상 20 이하인 노드: ");
    searchRange(root, 6, 20);                 // 함수 작성
    printf("\n");

    freeTree(root);
    return 0;
}

//출력예
// 전위 순회: 10 5 3 7 20 15 25
// 중위 순회: 3 5 7 10 15 20 25
// 후위 순회: 3 7 5 15 25 20 10
//
// 트리 높이: 2
// 전체 노드 수: 7
// 리프 노드 수: 4
// 노드 값 총합: 85
// 최댓값: 25
//
// 값이 6 이상 20 이하인 노드: 10 7 20 15