#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[50];
    char phoneNumber[15];
    struct Node* next;
} Node;

Node* insertContact(Node* head, const char* name, const char* phoneNumber) {

    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phoneNumber, phoneNumber);
    newNode->next = head;

    return newNode;
}

// 연락처를 검색하는 함수
Node* searchContact(Node* head, const char* name) {
    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;  // 찾은 노드를 반환
        }
        current = current->next;
    }
    return NULL;
}

Node* deleteContact(Node* head, const char* name) {
    if (head == NULL) {
        return NULL;
    }

    if (strcmp(head->name, name) == 0) {
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    Node* current = head;
    while (current->next != NULL) {
        if (strcmp(current->next->name, name) == 0) {
            Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
            return head;
        }
        current = current->next;
    }

    printf("연락처를 찾을 수 없습니다.\n");
    return head;
}

void printContacts(Node* head) {
    Node* current = head;
    if (current == NULL) {
        printf("전화번호부가 비어 있습니다.\n");
        return;
    }

    printf("전화번호부:\n");
    while (current != NULL) {
        printf("이름: %s, 전화번호: %s\n", current->name, current->phoneNumber);
        current = current->next;
    }
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Node* phonebook = NULL;  // 전화번호부의 헤드 포인터

    phonebook = insertContact(phonebook, "홍성민", "010-2275-7024");
    phonebook = insertContact(phonebook, "테스트1", "010-9876-5432");
    phonebook = insertContact(phonebook, "테스트2", "010-1122-3344");

    printContacts(phonebook);

    const char* searchName = "홍성민";
    Node* foundContact = searchContact(phonebook, searchName);
    if (foundContact) {
        printf("찾은 연락처 - 이름: %s, 전화번호: %s\n", foundContact->name, foundContact->phoneNumber);
    } else {
        printf("연락처 %s를 찾을 수 없습니다.\n", searchName);
    }

    const char* deleteName = "테스트2";
    phonebook = deleteContact(phonebook, deleteName);
    printf("\n%s의 연락처 삭제 후:\n", deleteName);
    printContacts(phonebook);

    freeList(phonebook);
    return 0;
}
