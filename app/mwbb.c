/**
 * mwbb.c -- реализует команду перемещения курсора в начало
 * текущего слова, если это возможно
 */

#include <stdio.h>
#include "common.h"
#include "_text.h"
#include "text.h"

void mwbb(text txt)
{
    /* проверяем, имеется ли текст */
    if (txt == NULL || txt->length == 0) {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return;
    }

    /* текст ненулевой длины должен содержать хотя бы одну строку */
    assert(txt->begin != NULL && txt->end != NULL);

    /* стартуем с начальной строки текста */
    node *current = txt->begin;

    int position = txt->cursor->position;
    int i;
    int fl = 0;

    /* к каждой строке текста применяем обработчик */
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

    char *contents = current->contents;

    /* цикл с поиском слова */
    for (i = position; contents[i] != ' '; i--) {
        printf("%c", contents[i]);
        /* находим позицию, где начинается предыдущее слово */
        if (contents[i-1] == ' ' || contents[i-1] == '?' || contents[i-1] == '.' || contents[i-1] == '!')  {
            txt->cursor->position = position;
            return;
        }
        /* продолжаем движение к началу слова */
        if (((int)contents[i] >= (int)'a') && (int)(contents[i] <= (int)'z')) {
            position--;
        }
        if (((int)contents[i] >= (int)'A') && ((int)contents[i] <= (int)'Z')) {
            position--;
        }
    }
    
    txt->cursor->position = position;
    return;
}