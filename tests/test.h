#ifndef TEST_H
#define TEST_H

#include <gtest/gtest.h>

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

extern "C" {
#include "../app/common.h"
#include "../app/text/_text.h"
#include "../app/text/text.h"
}

/* ----- move.c ----- */

// позитивный тест
TEST(test_move, positive) {

    text txt = create_text();
    load(txt, input);
    move(txt, 2, 3);

    //позиция в строке
    EXPECT_EQ(txt->cursor->position, 3);

    int line = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line) {
        line++;
        current = current->next;
    }

    EXPECT_EQ(line, 2);
    remove_all(txt);
}


#endif // SQUAREEQUALITY_TEST_H