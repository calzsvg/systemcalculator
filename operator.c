#include "header.h"

// 문자열 리스트로 변환
Node* stringToList(char* str) {
    Node* head = NULL;
    int i = 0;
    if (str[i] == '-') i++; 
    
    for (; str[i] != '\0'; i++) {
        if (isdigit(str[i])) {
            appendNode(&head, str[i] - '0');
        }
    }
    if (head == NULL) appendNode(&head, 0);
    return head;
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
    Node* res = NULL;
    Node* tA = getTail(A);
    Node* tB = getTail(B);
    int carry = 0;

    while (tA != NULL || tB != NULL || carry != 0) {
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
    Node* res = NULL;
    Node* tA = getTail(A);
    Node* tB = getTail(B);
    int borrow = 0;

    while (tA != NULL) {
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

//한자릿 수를 곱할때의 함수
Node* multonw(Node* head, int digit) {
    if (digit == 0) return stringToList("0");
    if (digit == 1) {
        Node* zero = stringToList("0");
        Node* res = add(head, zero);
        freeList(zero);
        return res;
    }

    Node* res = NULL;
    Node* curr = getTail(head);
    int carry = 0;

    while (curr != NULL || carry != 0) {
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
//큰 수를 곱할때의 함수
Node* mult(Node* A, Node* B) {
    if ((A->data == 0 && A->next == NULL) || (B->data == 0 && B->next == NULL)) {
        return stringToList("0");
    }

    Node* result = stringToList("0");
    Node* tB = getTail(B);
    int shift = 0;

    while (tB != NULL) {
        int digit = tB->data;
        
        if (digit != 0) {
            Node* partial = multone(A, digit);
            
            for (int i = 0; i < shift; i++) {
                appendNode(&partial, 0); 
            }

            Node* newResult = add(result, partial);
            
            freeList(result);
            freeList(partial);
            
            result = newResult;
        }

        shift++;
        tB = tB->prev;
    }
    
    removeLeadingZeros(&result);
    return result;
}
