/**
 * rc.c -- удаляет текущую строку
 */

#include <stdio.h>
#include "common.h"
#include "_text.h"
#include "text.h"

void rc(text txt)
{
    int fl = 0;
    node *current = txt->cursor->line;

    /* проверяем, имеется ли текст */
    if (txt == NULL || txt->length == 0) {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return;
    }

    /* проверяем наличие курсора */
    while (current) {
        if (txt->cursor->line == current) {
            fl = 1;
            break;
        }
        current = current->next;
    }


    /* проверяем наличие курсора в тексте */
    if (fl == 0) {
        fprintf(stderr, "No cursor in the text!\n");
        return;
    }


    /* текст ненулевой длины должен содержать хотя бы одну строку */
    assert(txt->begin != NULL && txt->end != NULL);


    /* если список изначально пуст, делать ничего не надо */
    if (txt->length == 0 || txt->cursor->line == 0) {
       return;
    }

    /* честно -- я не знаю, что происходит ниже. чистая магия :( */
    current = txt->cursor->line;
    //printf ("current: %s\n", current);
    current = current->previous;
    //printf ("current->previous: %s\n\n", current->previous);
    //printf ("current: %s\n\n", current);
    //show(txt);
    //printf("\n\n\n");
    if (current) {
        node *next = current->next;
        if (txt == NULL || current == 0 || txt->length == 0  || current->next == 0 || next->next == 0 ) {
           return;
        }
        //printf ("current->next: %s\n", current->next);
        current->next = next->next;
        //printf ("next->next: %s\n\n", next->next);
        //show(txt);
        //printf("\n\n\n");

        //printf ("next->next->previous: %s\n", next->next->previous);
        next->next->previous = current;
        //printf ("current: %s\n", current);
        //show(txt);
        //printf("\n\n\n");
       free(next);
       move (txt, 0, 0);
    }
}