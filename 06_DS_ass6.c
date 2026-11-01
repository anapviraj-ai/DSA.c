
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

char stack[MAX];
int top = -1;

int evalStack[MAX];
int evalTop = -1;

/* Push operator onto stack */
void push(char ch)
{
    stack[++top] = ch;
}

/* Pop operator from stack */
char pop()
{
    return stack[top--];
}

/* Determine operator precedence */
int precedence(char ch)
{
    if(ch == '^')
        return 3;
    else if(ch == '*' || ch == '/')
        return 2;
    else if(ch == '+' || ch == '-')
        return 1;
    else
        return 0;
}

/* Check whether character is an operator */
int isOperator(char ch)
{
    return (ch == '+' || ch == '-' ||
            ch == '*' || ch == '/' || ch == '^');
}

/* Convert Infix to Postfix */
void infixToPostfix(char infix[], char postfix[])
{
    int i, j = 0;
    char ch;

    for(i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        if(isalnum(ch))
        {
            postfix[j++] = ch;
        }

        else if(ch == '(')
        {
            push(ch);
        }

        else if(ch == ')')
        {
            while(top != -1 && stack[top] != '(')
            {
                postfix[j++] = pop();
            }

            if(top != -1)
                pop();
        }

        else if(isOperator(ch))
        {
            while(top != -1 &&
                  stack[top] != '(' &&
                  precedence(stack[top]) >= precedence(ch))
            {
                postfix[j++] = pop();
            }

            push(ch);
        }
    }

    while(top != -1)
    {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
}

/* Perform arithmetic operation */
int calculate(int operand1, int operand2, char operator)
{
    switch(operator)
    {
        case '+':
            return operand1 + operand2;

        case '-':
            return operand1 - operand2;

        case '*':
            return operand1 * operand2;

        case '/':
            return operand1 / operand2;

        case '^':
            return (int)pow(operand1, operand2);

        default:
            return 0;
    }
}

/* Evaluate Postfix Expression */
int evaluatePostfix(char postfix[])
{
    int i;
    char ch;
    int operand1, operand2, result;

    evalTop = -1;

    for(i = 0; postfix[i] != '\0'; i++)
    {
        ch = postfix[i];

        if(isdigit(ch))
        {
            evalStack[++evalTop] = ch - '0';
        }

        else if(isOperator(ch))
        {
            operand2 = evalStack[evalTop--];
            operand1 = evalStack[evalTop--];

            result = calculate(operand1, operand2, ch);

            evalStack[++evalTop] = result;
        }
    }

    return evalStack[evalTop];
}

/* Main Function */
int main()
{
    char infix[MAX];
    char postfix[MAX];
    int result;

    printf("Enter infix expression: ");
    scanf("%99s", infix);

    infixToPostfix(infix, postfix);

    printf("\nInfix Expression : %s", infix);
    printf("\nPostfix Expression : %s", postfix);

    result = evaluatePostfix(postfix);

    printf("\nResult: %d\n", result);

    return 0;
}
