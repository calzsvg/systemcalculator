#include "header.h"

void initStack(Stack* s) {
    s->top = NULL;
}

void push(Stack* s, char data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Out of Memory\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
}

char pop(Stack* s) {
    if (isEmpty(s)) {
        return 0;
    }
    StackNode* temp = s->top;
    char popData = temp->data;
    
    s->top = s->top->next;
    free(temp);
    
    return popData;
}

int isEmpty(Stack* s) {
    if (s->top == NULL)
        return 1;
    else
        return 0;
}

char peek(Stack* s) {
    if (isEmpty(s)) {
        return 0;
    }
    return s->top->data;
}