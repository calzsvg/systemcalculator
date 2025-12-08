#include <stdio.h>
#include <stdlib.h> /*나중에 header.h로 바꿀 예정*/

struct NODE
{
    struct NODE *next;
    int data;
};

struct POSTFIX
{
    struct postfix *next;
    int data;
};

void push(struct NODE *target, int data);
int pop(struct NODE *target);
void sequence(char equation);

int main()
{
    char infix[100];
    
    struct NODE *top = malloc(sizeof(struct NODE));
    struct POSTFIX *top2 = malloc(sizeof(struct POSTFIX));

    top -> next = NULL;
    top2 -> next = NULL;

    printf("수식을 입력해주세요: ");
    scanf("%s", &infix);

    for(int i=0 ; i<=100 ; i++)
    {
        if(48 < infix[i] && infix[i] < 57) /*char로 입력 -> int로 바꾸면 아스키코드로 인식*/
        {
            push(top2, infix[i]);
        }
        else if(40 < infix[i] && infix[i] < 47)
        {
            sequence(infix[i]);
            push(top, infix[i]);
        }

        for(int j=0 ; j<=5 ; j++)
        {
            int previous = top -> data;
        }

    }

    push(top, infix);
    pop(top);

    for(???)
    {
        printf("후위식으로 바꾼 식은 다음과 같습니다.: ") /*node에다가 아스키코드를 저장해서 이를 불러올 때 for문으로 node 옮겨가면서 불러야함*/

    }

    struct NODE *curr = top -> next;
    while(curr != NULL)     /*할당한 동적메모리를 해제 - POSTFIX에 대해서도 해야함*/
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

void sequencce(char equation)
{
    switch(equation)
    {
        case '+ , -':
            return 1;
        case '* , /':
            return 2;
        case '( , )':
            return 3;
    }
}