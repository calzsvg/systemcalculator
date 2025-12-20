#include "header.h"

int priority(char op) 
{
        switch (op) 
        {
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

Token* infix_postfix(Token* infixTokens)
{
    Token* postfixHead = newTokenList();
    Stack opStack;
    initStack(&opStack);

    Token* curr = infixTokens->next; /*헤더 다음부터 시작*/
    while (curr != NULL)
    {
        if (curr->type == 'N') /*숫자, parser.c의 타입 정의를 가져옴*/
        {
            addNumberToken(postfixHead, curr->number_head);
        }
        
        else if (curr->op == '(')   /*괄호 반영*/
        {
            push(&opStack, '(');
        }
        
        else if (curr->op == ')')
        {
            while (!isEmpty(&opStack) && peek(&opStack) != '(') /*isEmpty, pop, push: stack.c에서 가져옴*/
            {
                addOperatorToken(postfixHead, pop(&opStack));
            }
            pop(&opStack);  /*'(' 를 꺼냄*/
        }
        
        else /*연산자*/
        {
            while (!isEmpty(&opStack) && priority(peek(&opStack)) >= priority(curr->op))    /*연산자 우선순위 고려, */
            {
                addOperatorToken(postfixHead, pop(&opStack));
            }
            push(&opStack, curr->op);
        }
        curr = curr->next;
    }

    while (!isEmpty(&opStack))
    {
        addOperatorToken(postfixHead, pop(&opStack));
    }

    return postfixHead;
}