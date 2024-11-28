#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->data = data;
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
        *tail = node;
    } else {
        (*tail)->next = node;
        *tail = node;
    }
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL) return -1;

    struct node *temp = *head;
    int data = temp->data;
    *head = temp->next;

    if (*head == NULL) *tail = NULL;

    free(temp);
    return data;
}

void show(struct node *head) {
    struct node *cur = head;
    while (cur != NULL) {
        printf("%d\n", cur->data);
        cur = cur->next;
    }
}

int main(void) {
    struct node *head = NULL;
    struct node *tail = NULL;
    char input[100];

    while (1) {
        scanf("%s", input);

        int is_number = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                is_number = 0;
                break;
            }
        }

        if (is_number) {
            int num = atoi(input);
            addq(&head, &tail, num);
        } else {
            printf("Print queue\n");
            show(head);
			break;
        }
    }

    return 0;
}
