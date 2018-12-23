#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbl_linked_list.h"

#define MAXSIZE 99

int main(int argc, char **argv) {

    char input[12] = "";
    FILE *f;
    printf("Input file: ");
    scanf("%s", input);
    f = fopen(input, "r");
    printf("Writing tape...\n");
    struct Node *head = NULL;
    while (!feof(f)) {
        int count = 0;
        char *tape = (char *) malloc(MAXSIZE * sizeof(char));
        fgets(tape, MAXSIZE, f);
        char *initialTape = (char *) malloc(strlen(tape) * sizeof(char));
        sscanf(tape, "%s", initialTape);
        size_t test = sizeof(initialTape);
        while (count < test) {
            if (count == 0 && head == NULL) {
                push(&head, *(tape + count));
            } else if (*(tape + count) != '\n' && *(tape + count) != '\000') {
                append(&head, *(tape + count));
            }
            count++;
        }
        count = 0;
        if (*tape != '\000') {
            printf("Initial Tape Contents: ");
            printTape(head);
            printf("\n");
        }

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
        while (*stateNum > 0) {
            if (*state == *newState) {
                if (head->data == *readVal) {
                    head->data = *writeVal;
                    if (*moveDirection == 'R' && head->next != NULL) {
                        head = head->next;
                    } else if (*moveDirection == 'R' && head->next == NULL) {
                        fgets(tape, MAXSIZE, f);
                        sscanf(tape, "%d %c %c %c %d", state, readVal, writeVal, moveDirection, newState);
                        if (*state == *newState)
                            count++;
                        else
                            count--;
                        append(&head, *writeVal);
                        head = head->next;
                    } else if (*moveDirection == 'L' && head->prev != NULL) {
                        head = head->prev;
                    } else if (*moveDirection == 'L' && head->prev == NULL) {
                        fgets(tape, MAXSIZE, f);
                        sscanf(tape, "%d %c %c %c %d", state, readVal, writeVal, moveDirection, newState);
                        if (*state == *newState)
                            count++;
                        push(&head, 'B');
                    }
                } else
                    while (head->data != *readVal) {
                           if (count > 0 && head -> data != 'B') {
                               fseek(f, -20, SEEK_CUR);
                               fgets(tape, MAXSIZE, f);
                               count--;
                               sscanf(tape, "%d %c %c %c %d", state, readVal, writeVal, moveDirection, newState);
                           } else   {
                               fgets(tape, MAXSIZE, f);
                               sscanf(tape, "%d %c %c %c %d", state, readVal, writeVal, moveDirection, newState);
                               if (*state == *newState)
                                   count++;
                           }
                        if (head->data == *readVal)
                            break;
                        if (*state < *newState) {
                            head->data = *writeVal;
                            *stateNum = (*stateNum - 1);
                            if (*stateNum == 1) {
                                break;
                            }
                            if (*moveDirection == 'R' && head->next != NULL) {
                                head = head->next;
                            } else if (*moveDirection == 'R' && head->next == NULL) {
                                append(&head, *writeVal);
                                head = head->next;
                            } else if (*moveDirection == 'L' && head->prev != NULL) {
                                head = head->prev;
                            } else if (*moveDirection == 'L' && head->prev == NULL) {
                                push(&head, *writeVal);
                            }
                            fgets(tape, MAXSIZE, f);
                            sscanf(tape, "%d %c %c %c %d", state, readVal, writeVal, moveDirection, newState);
                            count = 0;
                        } else if (*state == *newState) {
                            head->data = *writeVal;
                            fgets(tape, MAXSIZE, f);
                            sscanf(tape, "%d %c %c %c %d", state, readVal, writeVal, moveDirection, newState);
                            if (*state == *newState)
                                count++;
                            if (head->data == *readVal)
                                break;
                            if (*moveDirection == 'R' && head->next != NULL) {
                                head = head->next;
                            } else if (*moveDirection == 'R' && head->next == NULL) {
                                append(&head, 'B');
                                head = head->next;
                            } else if (*moveDirection == 'L' && head->prev != NULL) {
                                head = head->prev;
                            } else if (*moveDirection == 'L' && head->prev == NULL) {
                                push(&head, *writeVal);
                            }
                        }
                    }
            } else if (*state < *newState) {
                head->data = *writeVal;
                *stateNum = (*stateNum - 1);
                if (*stateNum == 1) {
                    break;
                }
                if (*moveDirection == 'R' && head->next != NULL) {
                    head = head->next;
                } else if (*moveDirection == 'R' && head->next == NULL) {
                    append(&head, *writeVal);
                    head = head->next;
                } else if (*moveDirection == 'L' && head->prev != NULL) {
                    head = head->prev;
                } else if (*moveDirection == 'L' && head->prev == NULL) {
                    push(&head, *writeVal);
                }
                fgets(tape, MAXSIZE, f);
                sscanf(tape, "%d %c %c %c %d", state, readVal, writeVal, moveDirection, newState);
            }
        }
    }
    fclose(f);
    printf("Final Tape Contents: ");
    printTape(head);
    return 0;
}
