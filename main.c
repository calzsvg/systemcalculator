#include "header.h"

void freeTokenListShallow(Token* head) {
    Token* curr = head;
    while (curr != NULL) {
        Token* next = curr->next;
        free(curr);
        curr = next;
    }
}

// 입력 파일 예외처리
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
    buf[strcspn(buf, "\n")] = 0; // 입력식 줄바꿈 제거

    printf("입력수식 : %s\n", buf);


    Token *infixTokens = trans_token(buf);
    Token *postfixTokens = infix_postfix(infixTokens);

    // 후위식으로 변환 끝난 중위식 메모리 해제
    freeTokenListShallow(infixTokens);

    
    NodeStack calcStack;
    initNodeStack(&calcStack);

    Token *curr = postfixTokens->next; 

    
    while (curr != NULL) {
        if (curr->type == 'N') {
            pushNode(&calcStack, curr->number_head); // 숫자면 바로 push
        } 
        else if (curr->type == 'O') { // 연산자면 숫자 두개 pop 
            Node* B = popNode(&calcStack); // 스택 구조라 나중에 들어온 숫자부터 노드 B에 할당
            Node* A = popNode(&calcStack);
            Node* result = NULL;
            char op = curr->op;
            
            // 연산자 따라 함수 호출
            if (op == '+') result = add(A, B);
            else if (op == '-') {
                if (compare(A, B) >= 0) result = sub(A, B);
                else { // A보다 B가 크면 반대로 빼고 음수 기호 (-2) 넣기
                    result = sub(B, A);
                    insertAtHead(&result, -2); 
                }
            } 
            else if (op == '*') result = mult(A, B);
            else if (op == '/') result = division(A, B);


            // 사용한 피연산자 메모리 해제
            freeList(A);
            freeList(B);

            pushNode(&calcStack, result);
        }
        curr = curr->next;
    }

    // 결과 나온 후 후위식 메모리 해제
    freeTokenListShallow(postfixTokens);

    // 스택에 결과가 하나만 있으면 답 출력
    if (calcStack.top != NULL && calcStack.top->next == NULL) { 
        Node* finalResult = popNode(&calcStack);
        printf("답 : ");
        printList(finalResult);

        // 답 출력 후 사용했던 메모리 해제
        freeList(finalResult); 
    } 

    // 스택에 남은게 없거나 여러개면 오류 출력 예외처리
    else {
        printf("계산 오류");
        while (calcStack.top != NULL) {
            Node* leftover = popNode(&calcStack);
            freeList(leftover);
        }
    }

    return 0;
}