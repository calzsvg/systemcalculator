#include "header.h"

void error1(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(1);
}

Token* newTokenList() {
    Token* head = (Token*)malloc(sizeof(Token));
    if (head == NULL) error1("Token List memory error");
    head->next = NULL;
    return head;
}

void addNumberToken(Token* head, Node* num_list) {
    Token* newNode = (Token*)malloc(sizeof(Token));
    if (newNode == NULL) error1("Token Node memory error");
    
    newNode->type = 'N';
    newNode->op = '\0';
    newNode->number_head = num_list;
    newNode->next = NULL;
    
    Token* curr = head;
    while(curr->next != NULL) curr = curr->next;
    curr->next = newNode;
}

void addOperatorToken(Token* head, char op) {               
    Token* newNode = (Token*)malloc(sizeof(Token));
    if (newNode == NULL) error1("Token Node memory error");

    newNode->type = 'O';
    newNode->op = op;
    newNode->number_head = NULL;
    newNode->next = NULL;
    
    Token* curr = head;
    while(curr->next != NULL) curr = curr->next;
    curr->next = newNode;
}

Token* trans_token(const char *infix_str) {
    
    int len = strlen(infix_str);
    char *temp_str = (char*)malloc(len * 2 + 1);
    if (temp_str == NULL) error1("Memory allocation failed.");
    int j = 0;

    for (int i = 0; i < len; i++) {
        char x = infix_str[i];

        if (isspace(x)) continue;

        if (!isdigit(x) && !strchr("+-*/().", x)) {
            free(temp_str);
            error1("Invalid character");
        }

        if (isdigit(x) && (i + 1 < len) && infix_str[i + 1] == '(') {
            temp_str[j++] = x;
            temp_str[j++] = '*';
        } else if (x == ')' && (i + 1 < len) && (isdigit(infix_str[i + 1]) || infix_str[i + 1] == '(')) {
            temp_str[j++] = x;
            temp_str[j++] = '*';
        } else {
            temp_str[j++] = x;
        }
    }
    temp_str[j] = '\0';
    
    Token* token_head = newTokenList();
    Node* current_number_head = NULL;
    int in_number = 0;
    
    for (int i = 0; temp_str[i] != '\0'; i++) {
        char x = temp_str[i];

        if (isdigit(x) || x == '.') {
            if (!in_number) {
                current_number_head = NULL; 
                in_number = 1;
            }

            appendNode(&current_number_head, (x != '.') ? (x - '0') : -1);

        } else if (strchr("+-*/()", x)) {
            if (in_number) {

                addNumberToken(token_head, current_number_head);
                in_number = 0;
            }

            addOperatorToken(token_head, x);
        }
    }
    
    if (in_number) {
        addNumberToken(token_head, current_number_head);
    }
    
    free(temp_str);
    return token_head;
}

