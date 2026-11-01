
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Character Stack
typedef struct {
    char items[MAX];
    int top;
} CharStack;

// Integer Stack
typedef struct {
    int items[MAX];
    int top;
} IntStack;

// Stack Operations
void pushChar(CharStack *s, char val) {
    s->items[++s->top] = val;
}

char popChar(CharStack *s) {
    return s->items[s->top--];
}

char peekChar(CharStack *s) {
    return s->items[s->top];
}

int isEmpty(CharStack *s) {
    return s->top == -1;
}

// Operator Precedence
int precedence(char op) {
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

// Infix to Postfix Conversion
void infixToPostfix(char infix[], char postfix[]) {
    CharStack s;
    s.top = -1;

    int i = 0, k = 0;

    while (infix[i] != '\0') {

        if (isspace(infix[i])) {
            i++;
            continue;
        }

        if (isalnum(infix[i])) {
            postfix[k++] = infix[i];
        }

        else if (infix[i] == '(') {
            pushChar(&s, infix[i]);
        }

        else if (infix[i] == ')') {
            while (!isEmpty(&s) && peekChar(&s) != '(') {
                postfix[k++] = popChar(&s);
            }

            if (!isEmpty(&s))
                popChar(&s);
        }

        else {
            while (!isEmpty(&s) &&
                   peekChar(&s) != '(' &&
                   precedence(peekChar(&s)) >= precedence(infix[i])) {
                postfix[k++] = popChar(&s);
            }

            pushChar(&s, infix[i]);
        }

        i++;
    }

    while (!isEmpty(&s)) {
        postfix[k++] = popChar(&s);
    }

    postfix[k] = '\0';
}

// Integer Stack Operations
void pushInt(IntStack *s, int val) {
    s->items[++s->top] = val;
}

int popInt(IntStack *s) {
    return s->items[s->top--];
}

// Evaluate Postfix Expression
int evaluatePostfix(char postfix[]) {
    IntStack s;
    s.top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {

        if (isdigit(postfix[i])) {
            pushInt(&s, postfix[i] - '0');
        }

        else {
            int val2 = popInt(&s);
            int val1 = popInt(&s);

            switch (postfix[i]) {

                case '+':
                    pushInt(&s, val1 + val2);
                    break;

                case '-':
                    pushInt(&s, val1 - val2);
                    break;

                case '*':
                    pushInt(&s, val1 * val2);
                    break;

                case '/':
                    if (val2 == 0) {
                        printf("Division by zero is not allowed.\n");
                        return 0;
                    }
                    pushInt(&s, val1 / val2);
                    break;

                case '^': {
                    int result = 1;

                    for (int j = 0; j < val2; j++)
                        result *= val1;

                    pushInt(&s, result);
                    break;
                }
            }
        }
    }

    return popInt(&s);
}

// Main Function
int main() {

    char infix[MAX];
    char postfix[MAX];

    printf("Enter Infix Expression: ");
    fgets(infix, MAX, stdin);

    infixToPostfix(infix, postfix);

    printf("\nInfix Expression   : %s", infix);
    printf("Postfix Expression : %s\n", postfix);

    // Check whether expression contains only digits
    int numeric = 1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalpha(postfix[i])) {
            numeric = 0;
            break;
        }
    }

    if (numeric) {
        printf("Evaluation Result : %d\n",
               evaluatePostfix(postfix));
    }
    else {
        printf("Evaluation not possible: Expression contains characters.\n");
    }

    return 0;
}
