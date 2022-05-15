/**
 * shownoempty.c -- реализует команду вывода хранимого текста в прямом
 * порядке следования строк, кроме пустых строк
 */

#include <stdio.h>
#include <assert.h>
#include "common.h"
#include "text/text.h"

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
    UNUSED(cursor);
    UNUSED(data);
    
    if (cursor != -1) {
        char temp = contents[cursor];
        contents[cursor] = '\0';
        printf("%s", contents);
        printf("|");
        contents[cursor] = temp;
        printf("%s\n", contents + cursor);
        return;
    }
    
    /* Выводим строку на экран */
    printf("%s", contents);
}
