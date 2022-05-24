#ifndef EQTEST_H
#define EQTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <iostream>
#include <fstream>

extern "C" {
#include "common.h"
#include "_text.h"
#include "text.h"
}

char *input_missed_textsage = INPUTDIR "/missed_textsage.txt";

/* -------------------------- move.c -------------------------- */

// позитивный. первая строка, начало первого слова
TEST(test_move, positive_1) {
    text txt = create_text();
    load(txt, input_missed_textsage);

    move(txt,0,0);
    
    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("|Missed_textsage -- a small text game created by being impressed\n"
            "from the visual novel «missed messages.» created by Angela He. It shows how important it is to\n"
            "support the people around you, to show empathy and care. The game has\n"
            "several endings: good and bad, and it depends only on the player how the\n"
            "fate of the main character will go.\n"
            "Copyright (c) 18 may 2022, Sheglova Anastasia\n", output);

    remove_all(txt);
}


#endif // EQTEST_H
