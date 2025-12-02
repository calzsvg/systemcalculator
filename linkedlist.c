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
    while (curr != NULL) {
        printf("%d", curr->data);
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