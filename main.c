// NAME - JUSTIN MCQUAID
// DATE - FEBRUARY 18TH, 2019
// INSTRUCTOR - DANIEL SCHLEGEL
// COURSE - CSC344 PROGRAMMING LANGUAGES
// MAIN PROJECT 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "dbl_linked_list.h"

#define MAXSIZE 99


typedef struct {
    char write_value;
    char move_direction;
    int new_state;
} sheet;

int main(int argc, char **argv) {

    char input[12] = "";
    FILE *f;
    printf("Input file: ");
    scanf("%s", input);
    f = fopen(input, "r");
    printf("Writing tape...\n");
    struct Node *tape = NULL;
    while (!feof(f)) {
        int count = 0;
        char *file = (char *) malloc(MAXSIZE * sizeof(char));
        fgets(file, MAXSIZE, f);
        tape = malloc(sizeof(struct Node));
        for (count = 0; count < strlen(file) - 1; count++) {
            if (count == 0) {
                tape = insert(tape, *(file + count));
            } else {
                tape = insert_after(tape, *(file + count));
            }
        }
        if (*file != '\000') {
            printf("Initial Tape Contents: ");
            while (tape->prev != NULL) {
                tape = tape->prev;
            }
            while (tape->next != NULL) {
                printf("%c", tape->data);
                tape = tape->next;
            }
            printf("%c", tape->data);
            while (tape->prev != NULL) {
                tape = tape->prev;
            }
            printf("\n");
        }
        fgets(file, MAXSIZE, f);
        char *pos;
        if ((pos = strchr(file, '\n')) != NULL)
            *pos = '\0';
        sheet **instructions = malloc(((*file - '0')) * sizeof(sheet *));
        for (int i = 0; i < ((*file - '0')); i++) {
            instructions[i] = malloc(255 * sizeof(sheet));
        }
        if ((pos = strchr(file, '\n')) != NULL)
            *pos = '\0';
        fgets(file, MAXSIZE, f);
        int start_state = *file - '0';
        fgets(file, MAXSIZE, f);
        int end_state = *file - '0';
        while (fgets(file, MAXSIZE, f) != NULL) {
            instructions[*file - '0'][*(file + 2)].write_value = *(file + 4);
            instructions[*file - '0'][*(file + 2)].move_direction = *(file + 6);
            instructions[*file - '0'][*(file + 2)].new_state = *(file + 8) - '0';
        }
        file = NULL;
        free(file);
        while (start_state < end_state) {
            if (instructions[start_state][tape->data].move_direction == 'R' && tape->next != NULL) {
                char prev_head = tape->data;
                tape->data = instructions[start_state][tape->data].write_value;
                start_state = instructions[start_state][prev_head].new_state;
                tape = tape->next;
            } else if (instructions[start_state][tape->data].move_direction == 'L' && tape->prev != NULL) {
                char prev_head = tape->data;
                tape->data = instructions[start_state][tape->data].write_value;
                start_state = instructions[start_state][prev_head].new_state;
                tape = tape->prev;
            } else if (instructions[start_state][tape->data].move_direction == 'R' && tape->next == NULL) {
                char prev_head = tape->data;
                tape->data = instructions[start_state][tape->data].write_value;
                start_state = instructions[start_state][prev_head].new_state;
                tape = insert_after(tape, 'B');
            } else if (instructions[start_state][tape->data].move_direction == 'L' && tape->prev == NULL) {
                char prev_head = tape->data;
                tape->data = instructions[start_state][tape->data].write_value;
                start_state = instructions[start_state][prev_head].new_state;
                tape = insert_before(tape, 'B');
            }
        }
        printf("Final Tape Contents: ");
        while (tape->prev != NULL) {
            tape = tape->prev;
        }
        while (tape->next != NULL) {
            printf("%c", tape->data);
            tape = tape->next;
        }
        printf("%c", tape->data);
        printf("\n");
    }
    fclose(f);
    f = NULL;
    free(f);
    return 0;
}