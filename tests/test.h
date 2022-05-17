#ifndef QTEST_H
#define QTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <iostream>
#include <fstream>

extern "C" {
#include "common.h"
#include "_text.h"
#include "text.h"
}

char *input = INPUTDIR "/input.txt";
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