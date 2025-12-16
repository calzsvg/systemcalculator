#include "header.h"

int main() {
    char s1[100], s2[100], op;

    // input 파일 열기
    FILE *fp = fopen("input", "r");
    if (fscanf(fp, "%s %c %s", s1, &op, s2) != 3) {
        printf("Error: 파일 내용 형식이 잘못되었습니다.\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);


    printf("Input : %s %c %s\n", s1, op, s2);

    
    // 문자열 > 리스트
    Node* n1 = stringToList(s1);
    Node* n2 = stringToList(s2);
    Node* result = NULL;
    int isNegative = 0;
    
    if (op == '+') {
        result = add(n1, n2);
    } 
    else if (op == '-') {
        if (compare(n1, n2) >= 0) {
            result = sub(n1, n2);
        } else {
            isNegative = 1;
            result = sub(n2, n1);
        }
    }

    // 결과 출력
    printf("Result : ");
    if (isNegative) printf("-");
    printList(result);

    // 메모리 해제
    freeList(n1);
    freeList(n2);
    freeList(result);

    return 0;
}