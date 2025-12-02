#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct StackNode {
    char data;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    struct StackNode* top;
} Stack;

Node* createNode(int data);
void appendNode(Node** head, int data);
void printList(Node* head);
void freeList(Node* head);

void initStack(Stack* s);
void push(Stack* s, char data);
char pop(Stack* s);
int isEmpty(Stack* s);
char peek(Stack* s);

#endif