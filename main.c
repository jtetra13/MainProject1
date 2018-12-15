#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 99

struct Node {
    char data;
    struct Node *next;
    struct Node *prev;
};

void push(struct Node **headRef, int firstDigit) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->data = firstDigit;
    newNode->next = (*headRef);
    newNode->prev = NULL;
    if ((*headRef) != NULL) {
        (*headRef)->prev = newNode;
    }

    *headRef = newNode;
}

void append(struct Node **headRef, int newData) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    struct Node *last = *headRef;
    newNode->data = newData;
    newNode->next = NULL;
    if (*headRef == NULL) {
        newNode->prev = NULL;
        *headRef = newNode;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = newNode;
    newNode->prev = last;
}

void printTape(struct Node *node) {
    struct Node *last;
    while (node != NULL) {
        printf("%c", node->data);
        last = node;
        node = node->next;
    }
}

int main(int argc, char **argv) {

    char input[12] = "";
    int count = 0;
    FILE *f;
    struct Node *head = NULL;
    printf("Input file: ");
    scanf("%s", input);
    f = fopen(input, "r");
    printf("Writing tape...\n");
    while (!feof(f)) {
        char *tape = (char *) malloc(MAXSIZE * sizeof(char));
        fgets(tape, MAXSIZE, f);
        char *initialTape = (char *) malloc(strlen(tape) * sizeof(char));
        sscanf(tape, "%s", initialTape);
        size_t test = sizeof(initialTape);
        while (count < test) {
            if (count == 0) {
                push(&head, *(tape + count));
            } else if (*(tape + count) != '\n')  {
                append(&head, *(tape + count));
            }
            count++;
        }
        printf("Initial Tape Contents: ");
        printTape(head);
        printf("\n");
        fgets(tape, MAXSIZE, f);
        int *stateNum = (int *) malloc(1 * sizeof(int));
        sscanf(tape, "%d", stateNum);
        fgets(tape, MAXSIZE, f);
        int *startState = (int *) malloc(1 * sizeof(int));
        sscanf(tape, "%d", startState);
        fgets(tape, MAXSIZE, f);
        int *endState = (int *) malloc(1 * sizeof(int));
        sscanf(tape, "%d", endState);
        fgets(tape, MAXSIZE, f);
        int *state = (int *) malloc(1 * sizeof(int));
        char *readVal = (char *) malloc(1 * sizeof(char));
        char *writeVal = (char *) malloc(1 * sizeof(char));
        char *moveDirection = (char *) malloc(1 * sizeof(char));
        int *newState = (int *) malloc(1 * sizeof(int));
        sscanf(tape, "%d %c %c %c %d", state, readVal, writeVal, moveDirection, newState);
        while (*startState < *endState) {
            if (head->data == *readVal) {
                head->data = *writeVal;
                if (*moveDirection == 'R' && head->next != NULL) {
                    head -> data = *writeVal;
                    head = head -> next;
                } else if (*moveDirection == 'R' && head->next == NULL) {
                    fgets(tape, MAXSIZE, f);
                    sscanf(tape, "%d %c %c %c %d", state, readVal, writeVal, moveDirection, newState);
                    append(&head, *writeVal);
                    head = head->next;
                    *startState = *newState;
                } else if (*moveDirection == 'L' && head->prev != NULL) {
                    head = head->prev;
                    if (*state != *newState) {
                        fgets(tape, MAXSIZE, f);
                        sscanf(tape, "%d %c %c %c %d", state, readVal, writeVal, moveDirection, newState);
                    }
                } else if (*moveDirection == 'L' && head->prev == NULL) {
                    //fgets(tape, MAXSIZE, f);
                    //sscanf(tape, "%d %c %c %c %d", state, readVal, writeVal, moveDirection, newState);
                    push(&head, 'B');
                    *startState = *newState;
                }
            } else if (*moveDirection == 'R' && head->prev != NULL)   {
                fgets(tape, MAXSIZE, f);
                sscanf(tape, "%d %c %c %c %d", state, readVal, writeVal, moveDirection, newState);
            }
            head =head -> next;
        }
        fclose(f);
        printf("Final Tape Contents: ");
        printTape(head);
        return 0;
    }
}

