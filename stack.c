#include "header.h"

void initStack(Stack* s) {
    s->top = NULL;
}

void push(Stack* s, char data) {
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    temp->data = data;
    temp->next = s->top;
    s->top = temp;
}

char pop(Stack* s) {
    if (isEmpty(s)) {
        return 0;
    }
    StackNode* temp = s->top;
    char item = temp->data;
    s->top = s->top->next;
    free(temp);
    return item;
}

int isEmpty(Stack* s) {
    if (s->top == NULL) {
        return 1;
    } else {
        return 0;
    }
}

char peek(Stack* s) {
    if (isEmpty(s)) {
        return 0;
    }
    return s->top->data;
}