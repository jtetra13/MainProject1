// NAME - JUSTIN MCQUAID
// DATE - FEBRUARY 18TH, 2019
// INSTRUCTOR - DANIEL SCHLEGEL
// COURSE - CSC344 PROGRAMMING LANGUAGES
// MAIN PROJECT 1

#ifndef MAINPROJECT1_DBL_LINKED_LIST_H
#define MAINPROJECT1_DBL_LINKED_LIST_H

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
    node = last;
    while (node != NULL) {
        printf("%c", node->data);

        node = node->next;
    }
}

#endif //MAINPROJECT1_DBL_LINKED_LIST_H
