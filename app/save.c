/**
 * save.c - функция сохранения текста
 */

#include <stdio.h>
#include "common.h"
#include "_text.h"
#include "text.h"


void save(text txt, char *filename) {

    FILE *f;

    /* ПРоверяем, имеется ли текст */
    if (txt == NULL || txt->length == 0) {
        fprintf(stderr, "The text doesn't exist\n");
        return;
    }

    /* Открываем файл для чтения, контролируя ошибки */
    if ((f = fopen(filename, "w")) == NULL) {
        fprintf(stderr, "File %s can't be opened\n", filename);
        return;
    }

    /* Текст ненулевой длины должен содержать хотя бы одну строку*/
    assert(txt->begin != NULL && txt->end != NULL);

    /* Стартуем с начальной точки текста */
    node *current = txt->begin;

    do {
        fprintf(f, "%s\n", current->contents);
        current = current->next;
    } while(current);

    fprintf(stdout, "Save file successeed!\n");
    fclose (f);
}
