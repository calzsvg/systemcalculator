#include "header.h"

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Out of Memory\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* curr = *head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
        newNode->prev = curr;
    }
}

void printList(Node* head) {
    Node* curr = head;
    if (curr == NULL) return;
    if (curr->data == -2) {
        printf("-");
        curr = curr->next;
    }

    while (curr != NULL) {
        if (curr->data == -1) printf("."); // 소수점
        else if (curr->data >= 0) printf("%d", curr->data); // 숫자만
        curr = curr->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
}
 