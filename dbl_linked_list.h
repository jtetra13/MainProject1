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

struct Node * insert(struct Node *head, int d) {
    struct Node *new_node = malloc(sizeof(struct Node));
    new_node->data = d;
    return new_node;
}

struct Node * insert_after(struct Node *head, int d) {
    if (head->next == NULL) {
        struct Node *next_node=malloc(sizeof(struct Node));
        head->next = next_node;
        next_node->prev = head;
        head = next_node;
        next_node->data = d;
        next_node->next = NULL;
        return next_node;
    }

}

struct Node * insert_before(struct Node *head, int d)    {
    if (head -> prev == NULL)   {
        struct Node *prev_node = malloc(sizeof(struct Node));
        head->prev = prev_node;
        prev_node->next = head;
        head = prev_node;
        prev_node->data=d;
        prev_node -> prev = NULL;
        return prev_node;
    }
}

#endif //MAINPROJECT1_DBL_LINKED_LIST_H
