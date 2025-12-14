#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

/*#include "header.h"*/

struct datas
{
    enum {operator, value} kind;
    union
    {
        char op;
        int val;
    } uni;   
};
typedef struct datas datas;

struct elem
{
    datas    d;
    struct elem *next;
};
typedef struct elem elem;

struct stack
{
    int cnt;
    elem *top;
};
typedef struct stack stack;
typedef enum {false, true} boolean;

void    initialize(stack *stk);
void    push(datas d, stack *stk);
datas   pop(stack *stk);
boolean empty(const stack *stk);
int     priority(char op);
void    infix_to_postfix(const char *expr);

int main()
{
    const char *expression = "16 + 34 * 57 / 6";    /*나중에는 수식을 작성해서 scanf로 받게끔 만들어야함*/
    
    printf("수식(infix): %s\n", expression);
    printf("변경 후 수식(postfix): ");
    infix_to_postfix(expression);
    printf("\n");
    
    return 0;
}

void initialize(stack *stk)
{
    stk -> cnt = 0;
    stk -> top = NULL;
}

void push(datas d, stack *stk)
{
    elem *pushnode;
    pushnode = malloc(sizeof(elem));

    pushnode -> d = d;
    pushnode -> next = stk -> top;
    stk -> top = pushnode;
    stk -> cnt++;
}

datas pop(stack *stk)
{
    datas data;
    elem *popnode;

    popnode = stk -> top;
    data = stk -> top -> d;
    stk -> top = stk -> top -> next;
    stk -> cnt--;
    
    free(popnode);
    return data;
}

boolean empty(const stack *stk)
{
    return (stk -> cnt == 0) ? true : false;    /*if문 짧게 쓴거*/
}

int priority(char op)
{
    switch (op) {
        case '*': 
        case '/': 
            return 2;
        case '+': 
        case '-': 
            return 1;
        default:  
            return 0;       /*연산자 우선순위 부여*/
    }
}

void infix_to_postfix(const char *str)
{
    stack op_stack;
    initialize(&op_stack);
    
    const char *p = str;    /*입력 받은 수식*/
    datas d;

    while (*p != '\0')
    {
        if (isspace(*p))    /*공백*/
        {
            p++;
            continue;
        }

        if (isdigit(*p))    /*숫자*/
        {
            int num = 0;
            while (isdigit(*p))
            {
                num = num * 10 + (*p - '0');    /*문자열 숫자 -> int, 아스키코드를 이용*/
                p++;
            }
            printf("%d ", num); 
            continue; 
        }

        else if (*p == '+' || *p == '-' || *p == '*' || *p == '/')  /*연산자*/
        {
            while (!empty(&op_stack) && priority(op_stack.top->d.uni.op) >= priority(*p))   /*현재 연산자 >= 맨 위 연산자*/
            {
                datas popped = pop(&op_stack);
                printf("%c ", popped.uni.op);   /*연산자 출력*/
            }

            d.kind = operator;
            d.uni.op = *p;
            push(d, &op_stack);
            p++;
        }
        else {
            p++;    /*숫자, 연산자를 제외한 나머지 문자: pass*/
        }
    }

    while (!empty(&op_stack)) {
        datas popped = pop(&op_stack);
        printf("%c ", popped.uni.op);   /*연산자 출력2*/
    }
}