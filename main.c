#include "header.h"

void freeTokenListShallow(Token* head) {
    Token* curr = head;
    while (curr != NULL) {
        Token* next = curr->next;
        free(curr);
        curr = next;
    }
}

int main() {
    FILE *fp = fopen("input", "r");
    if (!fp) {
        printf("파일을 열 수 없습니다.");
        return 1;
    }

    char buf[2048];
    if (!fgets(buf, sizeof(buf), fp)) {
        printf("읽을 수식이 없습니다.");
        fclose(fp);
        return 1;
    }
    fclose(fp);
    buf[strcspn(buf, "\n")] = 0; // 줄바꿈 제거

    printf("입력수식 : %s\n", buf);


    Token *infixTokens = trans_token(buf);
    Token *postfixTokens = infix_postfix(infixTokens);

    freeTokenListShallow(infixTokens);

    
    NodeStack calcStack;
    initNodeStack(&calcStack);

    Token *curr = postfixTokens->next; 

    while (curr != NULL) {
        if (curr->type == 'N') {
            pushNode(&calcStack, curr->number_head);
        } 
        else if (curr->type == 'O') {
            Node* B = popNode(&calcStack);
            Node* A = popNode(&calcStack);
            Node* result = NULL;
            char op = curr->op;

            if (op == '+') result = add(A, B);
            else if (op == '-') {
                if (compare(A, B) >= 0) result = sub(A, B);
                else {
                    result = sub(B, A);
                    insertAtHead(&result, -2); 
                }
            } 
            else if (op == '*') result = mult(A, B);
            else if (op == '/') result = division(A, B);

        
            freeList(A);
            freeList(B);

            pushNode(&calcStack, result);
        }
        curr = curr->next;
    }


    freeTokenListShallow(postfixTokens);

    if (calcStack.top == 0) { 
        Node* finalResult = popNode(&calcStack);
        printf("답 : ");
        printList(finalResult);
        freeList(finalResult); 
    } 
    else {
        printf("계산 오류");
        while (calcStack.top != -1) {
            Node* leftover = popNode(&calcStack);
            freeList(leftover);
        }
    }

    return 0;
}