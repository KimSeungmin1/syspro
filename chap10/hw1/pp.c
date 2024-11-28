#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

void push(Stack *stack, int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    node->data = data;
    node->next = stack->top;
    stack->top = node;
}

int pop(Stack *stack) {
    if (stack->top == NULL) {
        printf("Stack underflow!\n");
        return -1;
    }

    Node *node = stack->top;
    int data = node->data;
    stack->top = node->next;
    free(node);

    return data;
}

void show(Stack *stack) {
    Node *cur = stack->top;
    while (cur != NULL) {
        printf("%d\n", cur->data);
        cur = cur->next;
    }
}

int main(void) {
    Stack s;
    s.top = NULL;

    char input[100];
    while (1) {
       // printf(">> ");
        if (scanf("%s", input) != 1) break;

        char *ptr = input;
        int is_number = 1;
        while (*ptr) {
            if (!isdigit(*ptr)) {
                is_number = 0;
                break;
            }
            ptr++;
        }

        if (is_number) {
            int num = atoi(input); 
            push(&s, num);
        } else {
            printf("Print stack\n");
            show(&s);
            break;
        }
    }

    return 0;
}

