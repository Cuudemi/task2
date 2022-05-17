/**
 * move.c -- реализует команду перемещения в заданную позицию 
 */

#include <stdio.h>
#include "common.h"
#include "_text.h"
#include "text.h"

void move(text txt, int line, int pose)
{
    /* Стартуем с начальной точки текста */
    node *current = txt->begin;
    
    int k;
    if (pose >= 0) {
        txt->cursor->position = pose;
    } else {
        txt->cursor->position = 0;
    }

    if (line > 0) {
        int l = txt->length;
        if (line > l)
            line = l;

        while (current) {
            if (k == line) {
                txt->cursor->line = current;
                break;
            }
            current = current->next;
            k++;
        }
    }
    else {
        txt->cursor->line = current;
    }
}