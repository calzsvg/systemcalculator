#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct NODE     /*구조체 이름*/
{
    struct NODE *next;
    int data;   /*자료형 변수명*/
};

struct postfix
{
    struct postfix *next;
    int data;
};

void push(struct NODE *target, int data);
int pop(struct NODE *target);

int main()
{
    int fomular;

    struct NODE *top = malloc(sizeof(struct NODE));     /*구조체를 쓰기 위해 변수로 선언해야함*/

    top -> next = NULL;

    printf("수식을 입력해주세요: ");
    scanf("%u", &fomular);
    top -> data = fomular;

    push(top, fomular);
    pop(top);

    printf("후위식으로 바꾼 식은 다음과 같습니다.: %d", fomular);

    struct NODE *curr = top -> next;
    while(curr != NULL)     /*할당한 동적메모리를 해제*/
    {
        struct NODE *next = curr -> next;
        free(curr);
        curr = next;
    }
    free(top);

    return 0;
}

void push(struct NODE *target, int data)
{
    struct NODE *pushNode = malloc(sizeof(struct NODE));
    pushNode -> data = data;

    pushNode -> next = target -> next;
    target -> next = pushNode;
}/*push -> node를 추가함으로써 구현*/

int pop(struct NODE *target)
{
    int popData;
    struct NODE *pop = target -> next;

    popData = pop -> data;
    target -> next = pop -> next;

    return popData;
}
/*pop: call by address를 통해 pop를 계속 바꿔서 구현*/
/*https://studyc.tistory.com/21 :c언어 함수에 대하여 잘 설명함, call by value, call by address 등*/

/*수정 테스트*/
