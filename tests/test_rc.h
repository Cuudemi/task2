#ifndef EQTEST_RC_H
#define EQTEST_RC_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <iostream>
#include <fstream>

extern "C" {
#include "common.h"
#include "_text.h"
#include "text.h"
}

// позитивный. загрузка файла, удаление строки
TEST(test_rc, positive_1) {
    text txt = create_text();
    load(txt, input_text);

    move(txt,6,3);
    rc(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("|He was indeed a deplorable spectacle. In the\n"
            "dim light of a foggy November day the sick room\n"
            "was a gloomy spot, but it was that gaunt, wasted\n"
            "face staring at me from the bed which sent a chill\n"
            "to my heart. His eyes had the brightness of fever,\n"
            "there was a hectic flush upon either cheek, and dark\n"
            "coverlet twitched incessantly, his voice was croaking and spasmodic. He lay listlessly as I entered\n"
            "the room, but the sight of me brought a gleam of\n"
            "recognition to his eyes.\n\n"

            "“Well, Watson, we seem to have fallen upon evil\n"
            "days,” said he in a feeble voice, but with something\n"
            "of his old carelessness of manner.\n", output);

    remove_all(txt);
}

// негативный. загрузка пустого файла
TEST(test_rc, negative_1) {
    text txt = create_text();
    load(txt, input_empty);

    move(txt,0,0);

    testing::internal::CaptureStderr();
    rc(txt);
    std::string output = testing::internal::GetCapturedStderr();

    ASSERT_EQ("There are already no any lines in the text!\n", output);

    remove_all(txt);
}
#endif // EQTEST_RC_H