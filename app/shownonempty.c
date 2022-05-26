/**
 * show.c -- реализует команду вывода хранимого текста на экран
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <assert.h>
#include "common.h"
#include "text.h"

static void show_line(int index, char *contents, int cursor, void *data);

/**
 * Выводит содержимое указанного файла на экран
 */
void shownonempty(text txt)
{
    /* Применяем функцию show_line к каждой строке текста */
    process_forward(txt, show_line, NULL);
}

/**
 * Выводит содержимое указанного файла на экран
 */
static void show_line(int index, char *contents, int cursor, void *data)
{

    /* Функция обработчик всегда получает существующую строку */
    assert(contents != NULL);
    
    /* Декларируем неиспользуемые параметры */
    UNUSED(index);
    UNUSED(data);
    
    int len_str = strlen(contents) - 1;
    int len = len_str > cursor ? len_str : cursor;

    /* если строка пустая (имеет размер -1), то пропускаем её */
    /* и идем к следующей */
    if (len_str < 0)
        return;

    for (int i = 0; i<= len; i++) {

        if (i == cursor)
            printf ("|");

        if (i <= len_str) {

        printf("%c", contents[i]);
        }

        else if (i < len) 
            printf(" ");
    }

    printf("\n");

}