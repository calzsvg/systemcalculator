#include "header.h"

// 소수점(-1)은 제외하고 새 리스트로 복사
Node* copyAsInteger(Node* src) {
    Node* newHead = NULL;
    Node* curr = src;
    int hasData = 0;
    
    while (curr != NULL) {
        if (curr->data != -1) {
            appendNode(&newHead, curr->data);
            hasData = 1;
        }
        curr = curr->next;
    }
    if (!hasData) appendNode(&newHead, 0);
    return newHead;
}

// 원본용 리스트 깊은 복사
Node* deepCopy(Node* src) {
    Node* newHead = NULL;
    Node* curr = src;
    if (curr == NULL) return stringToList("0");
    
    while (curr != NULL) {
        appendNode(&newHead, curr->data);
        curr = curr->next;
    }
    return newHead;
}

// 문자열 리스트로 변환
Node* stringToList(char* str) {
    Node* head = NULL;
    int i = 0;
    if (str[i] == '-') i++; 
    
    for (; str[i] != '\0'; i++) {
        if (isdigit(str[i])) {
            appendNode(&head, str[i] - '0');
        }
        else if (str[i] == '.') {
            appendNode(&head, -1);
        }
    }
    if (head == NULL) appendNode(&head, 0);
    return head;
}
// 소수점 아래 자릿수 세기
int getDecimalCount(Node* head) {
    Node* curr = head;
    int count = 0;
    int foundDot = 0;
    while (curr != NULL) {
        if (curr->data == -1) {
            foundDot = 1;
            count = 0;
        } else if (foundDot) {
            count++;
        }
        curr = curr->next;
    }
    return foundDot ? count : 0;
}

// 소수점 자릿수를 똑같이 맞춤 (덧셈 뺄셈)
void alignDecimals(Node* A, Node* B) {
    int decimalA = getDecimalCount(A);
    int decimalB = getDecimalCount(B);
    
    // 둘 다 소수점 없으면 패스
    if (decimalA == 0 && decimalB == 0 && getTail(A)->data != -1 && getTail(B)->data != -1) return;

    // 둘 중에 하나만 정수면 끝에 소수점(-1) 추가
    if (decimalA == 0 && getTail(A)->data != -1) appendNode(&A, -1);
    if (decimalB == 0 && getTail(B)->data != -1) appendNode(&B, -1);

    decimalA = getDecimalCount(A);
    decimalB = getDecimalCount(B);

    // 자릿수 차이만큼 0 추가
    if (decimalA < decimalB) {
        for (int i = 0; i < (decimalB - decimalA); i++) appendNode(&A, 0);
    } else if (decimalB < decimalA) {
        for (int i = 0; i < (decimalA - decimalB); i++) appendNode(&B, 0);
    }
}

// 리스트 꼬리 찾기
Node* getTail(Node* head) {
    if (head == NULL) return NULL;
    Node* curr = head;
    while (curr->next != NULL) curr = curr->next;
    return curr;
}

// 리스트 앞에서부터 추가
void insertAtHead(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
}

// 앞쪽 0 제거 후 메모리 해제
void removeLeadingZeros(Node** head) {
    while (*head != NULL && (*head)->data == 0 && (*head)->next != NULL) {
    	// 바로 뒤가 소수점이면 패스
        if ((*head)->next->data == -1) break;
        Node* temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}


int compare(Node* A, Node* B) {
    removeLeadingZeros(&A); 
    removeLeadingZeros(&B);

    // 길이 비교
    int lenA = 0, lenB = 0;
    Node* curr = A; while(curr){ lenA++; curr=curr->next; }
    curr = B; while(curr){ lenB++; curr=curr->next; }

    if (lenA > lenB) return 1;
    if (lenA < lenB) return -1;

    // 길이 같으면 앞에서부터 크기 비교
    Node* tA = A;
    Node* tB = B;
    while (tA != NULL) {
        if (tA->data > tB->data) return 1;
        if (tA->data < tB->data) return -1;
        tA = tA->next;
        tB = tB->next;
    }
    return 0;
}

// 덧셈
Node* add(Node* A, Node* B) {
    alignDecimals(A, B);
    Node* res = NULL;
    Node* tA = getTail(A);
    Node* tB = getTail(B);
    int carry = 0;
    
    while (tA != NULL || tB != NULL || carry != 0) {

        if (tA != NULL && tA->data == -1) {
            insertAtHead(&res, -1);
            tA = tA->prev;
            if (tB != NULL) tB = tB->prev;
        }

        int sum = carry;
        if (tA != NULL) { sum += tA->data; tA = tA->prev; }
        if (tB != NULL) { sum += tB->data; tB = tB->prev; }

        carry = sum / 10;
        insertAtHead(&res, sum % 10);
    }
    return res;
}

// 뺄셈
Node* sub(Node* A, Node* B) {
    alignDecimals(A, B);
    Node* res = NULL;
    Node* tA = getTail(A);
    Node* tB = getTail(B);
    int borrow = 0;

    while (tA != NULL) {
        if (tA->data == -1) {
            insertAtHead(&res, -1);
            tA = tA->prev;
            if (tB != NULL) tB = tB->prev;
            continue;
        }
        int valA = tA->data;
        int valB = (tB != NULL) ? tB->data : 0;
        
        valA = valA - borrow - valB;

        if (valA < 0) {
            valA += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        insertAtHead(&res, valA);
        
        tA = tA->prev;
        if (tB != NULL) tB = tB->prev;
    }
    removeLeadingZeros(&res);
    return res;
}

/*곱셈 : 12.3 * 1.23 이 있을 경우 123 * 123 처럼 정수로 만들고 곱셈을 수행한 후 소숫점을 찍는 방식
1. 소숫점 자릿수 파악
2. 정수 곱셈
3. 소숫점 입력*/

// 한 자리 수 곱셈 (소수점 무시 추가)
Node* multone(Node* head, int digit) {
    if (digit == 0) return stringToList("0");
    
    Node* res = NULL;
    Node* curr = getTail(head);
    int carry = 0;

    while (curr != NULL || carry != 0) {
        // 소수점(-1) 건너뜀
        if (curr != NULL && curr->data == -1) {
            curr = curr->prev;
            continue; 
        }

        int sum = carry;
        if (curr != NULL) {
            sum += (curr->data * digit);
            curr = curr->prev;
        }

        carry = sum / 10;
        insertAtHead(&res, sum % 10);
    }
    return res;
}

// 전체 곱셈 (소수점 처리 수정)
Node* mult(Node* A, Node* B) {
    if (A == NULL || B == NULL) return stringToList("0");

    int cntA = getDecimalCount(A);
    int cntB = getDecimalCount(B);
    
    // 곱셈 중에는 소수점이 없는 '정수 복사본'으로 계산하여 alignDecimals의 노드 생성을 막음
    Node* intA = copyAsInteger(A);
    Node* intB = copyAsInteger(B);
    
    Node* result = stringToList("0");
    Node* tB = getTail(intB);
    int shift = 0;

    while (tB != NULL) {
        // 소수점 건너뜀
        if (tB->data == -1) { tB = tB->prev; continue; }
        
        // 소수점을 무시하고 정수 곱셈 수행
        Node* partial = multone(intA, tB->data);
        
        // 자릿수 시프트 (10의 거듭제곱 꼴 곱셈)
        for (int i = 0; i < shift; i++) appendNode(&partial, 0);
        
        Node* tempSum = add(result, partial);
        
    
        freeList(result);
        freeList(partial);
        
        result = tempSum;
        shift++;
        tB = tB->prev;
    }

    // 결과에 소수점 합침
    int totalDecimals = cntA + cntB;
    if (totalDecimals > 0) {
        Node* dotPos = getTail(result);
        
        // 소수점 위치 (뒤에서부터 totalDecimals 만큼 이동)
        for (int i = 0; i < totalDecimals; i++) {
            if (dotPos && dotPos->prev == NULL) insertAtHead(&result, 0);
            else if (dotPos) dotPos = dotPos->prev;
        }
        if (dotPos) {
            Node* dot = createNode(-1);
            dot->next = dotPos->next;
            dot->prev = dotPos;
            if (dotPos->next) dotPos->next->prev = dot;
            dotPos->next = dot;
        }
    }

    freeList(intA);
    freeList(intB);
    removeLeadingZeros(&result);
    return result;
}
    
// 나눗셈

// 정수 나눗셈
Node* integerDivOnly(Node* A, Node* B) {
    Node* quotient = NULL;
    Node* remainder = stringToList("0");
    Node* curr = A;


    while (curr != NULL) {
        appendNode(&remainder, curr->data);
        removeLeadingZeros(&remainder);

        int count = 0;
        // 뺄셈 반복
        while (compare(remainder, B) >= 0) {
            Node* temp = sub(remainder, B);
            freeList(remainder);
            remainder = temp;
            count++;
        }
        appendNode(&quotient, count);
        curr = curr->next;
    }
    
    removeLeadingZeros(&quotient);
    freeList(remainder);
    return quotient;
}

// 소수 나눗셈 
Node* division(Node* A, Node* B) {
    // 원본 수가 수정되지 않도록 복사해서 계산
    Node* copyA = deepCopy(A);
    Node* copyB = deepCopy(B);
    alignDecimals(copyA, copyB);

    // 소수점 제거
    Node* intA = copyAsInteger(copyA);
    Node* intB = copyAsInteger(copyB);

    // 리스트 해제
    freeList(copyA);
    freeList(copyB);

    // 정수 나눗셈
    Node* result = integerDivOnly(intA, intB);
    Node* prod = mult(result, intB);
    Node* remainder = sub(intA, prod);
    freeList(prod);

    // 나머지 0이면 바로 리턴
    if (remainder->data == 0 && remainder->next == NULL) {
        freeList(remainder);
        freeList(intA);
        freeList(intB);
        return result;
    }

    // 소수점 아래 계산
    appendNode(&result, -1); // '.' 추가

    int precision = 12; // 12자리까지 계산
    for (int i = 0; i < precision; i++) {
        if (remainder->data == 0 && remainder->next == NULL) break;

        // 나머지 * 10 > 다시 다음 자릿수 계산
        appendNode(&remainder, 0); 
        removeLeadingZeros(&remainder);

        Node* digitNode = integerDivOnly(remainder, intB);
        
        // digitNode 앞에 0이 붙어있을 수 있기 때문에 tail값 사용
        appendNode(&result, getTail(digitNode)->data);

        // 다음 나머지 계산
        Node* tempProd = mult(digitNode, intB);
        Node* nextRem = sub(remainder, tempProd);

        freeList(remainder);
        freeList(tempProd);
        freeList(digitNode);

        remainder = nextRem;
    }

    // 메모리 해제
    freeList(remainder);
    freeList(intA);
    freeList(intB);

    return result;
}