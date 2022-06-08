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

    current = txt->cursor->line;
    current = current->previous;
    if (current) {
        node *next = current->next;
        if (txt == NULL || current == 0 || txt->length == 0  || current->next == 0 || next->next == 0 ) {
           return;
        }
        current->next = next->next;
        next->next->previous = current;
       free(next);
       move (txt, 0, 0);
    }
}