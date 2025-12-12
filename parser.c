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
    char *clean_str = (char*)malloc(len + 1);
    if (clean_str == NULL) error1("Memory allocation failed.");

    int k = 0;
    for (int i = 0; i < len; i++) {
        if (!isspace(infix_str[i])) {
            clean_str[k++] = infix_str[i];
        }
    }
    clean_str[k] = '\0';

    int clean_str_len = k;
    char *temp_str = (char*)malloc(clean_str_len * 2 + 1);
    if (temp_str == NULL) {
        free(clean_str); 
        error1("Memory allocation failed.");
    }
    
    int j = 0;
    for (int i = 0; i < clean_str_len; i++) {
        char x = clean_str[i];

        if (!isdigit(x) && !strchr("+-*/().", x)) {
            free(clean_str);
            free(temp_str);
            error1("Invalid character found");
        }

        if (isdigit(x) && (i + 1 < clean_str_len) && clean_str[i + 1] == '(') {
            temp_str[j++] = x;
            temp_str[j++] = '*';
        } 

        else if (x == ')' && (i + 1 < clean_str_len) && (isdigit(clean_str[i + 1]) || clean_str[i + 1] == '(')) {
            temp_str[j++] = x;
            temp_str[j++] = '*';
        } 
        else {
            temp_str[j++] = x;
        }
    }
    temp_str[j] = '\0';
    
    free(clean_str); 

    Token* token_head = initTokenList();
    Node* current_number_head = NULL;
    int is_number = 0;
    
    for (int i = 0; temp_str[i] != '\0'; i++) {
        char x = temp_str[i];

        if (isdigit(x) || x == '.') {
            if (!is_number) {
                current_number_head = NULL; 
                is_number = 1;
            }

            appendNode(&current_number_head, (x != '.') ? (x - '0') : -1);

        } else if (strchr("+-*/()", x)) {
            if (is_number) {
                
                addNumberToken(token_head, current_number_head);
                is_number = 0;
            }

            addOperatorToken(token_head, x);
        }
    }
    

    if (is_number) {
        addNumberToken(token_head, current_number_head);
    }
    
    free(temp_str);
    return token_head;
}

