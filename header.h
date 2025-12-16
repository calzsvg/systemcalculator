#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

typedef struct Token {
    char type;
    char op;
    Node* number_head;
    struct Token* next;
} Token;

Token* newTokenList();
Token* trans_token(const char *infix_str);

void addNumberToken(Token* head, Node* num_list);
void addOperatorToken(Token* head, char op);
void freeTokenList(Token* head);

Node* stringToList(char* str); 
Node* getTail(Node* head);
void insertAtHead(Node** head, int data);
void removeLeadingZeros(Node** head);
int compare(Node* A, Node* B);


Node* add(Node* A, Node* B); 
Node* sub(Node* A, Node* B);
Node* mult(Node* A, Node* B);
Node* division(Node* A, Node* B);


#endif