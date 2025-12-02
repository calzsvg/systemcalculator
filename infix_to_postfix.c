#include <header.h>

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
    unsigned infix;

    struct NODE *top = malloc(sizeof(struct NODE));     /*구조체를 쓰기 위해 변수로 선언해야함*/

    top -> next = NULL;

    printf("수식을 입력해주세요: ");
    scanf("%u", &infix);

    for(int i=1 ; i<=(입력받은 문장 길이) ; i++)
    {
        if(문장 내에 문자가 숫자)
        {
            postfix -> data = 문장 내에 숫자;
        }
        if(문장 내에 문자가 문자(+,-,*,/))
        {
            push(top, 문장 내에 문자);
        }

        for(int j=1 ; j<=(받은 문자 갯수?); j++)
        {
            if(사칙연산 우선순위 비교해서 우선순위 높음)
            {
                pop(top);
            }
            else if(우선순위 비교 -> 우선순위 낮음)
            {
                push(top, 문자);
            }

            if(받은 문자가 ')')
            {
                pop(top) /*스택 내에 '('까지 모든 문자 pop*/
            }
        }

    }

    printf("후위식으로 바꾼 식은 다음과 같습니다.: %d", postfix);

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
}

int pop(struct NODE *target)
{
    int popData;
    struct NODE *pop = target -> next;

    popData = pop -> data;
    target -> next = pop -> next;

    return popData;
}