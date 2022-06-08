#ifndef EQTEST_SNE_H
#define EQTEST_SNE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <iostream>
#include <fstream>

extern "C" {
#include "common.h"
#include "_text.h"
#include "text.h"
}

// позитивный. текст с одной пустой строкой
TEST(test_shownonempty, positive_1) {
    text txt = create_text();
    load(txt, input_text);

    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStdout();
    shownonempty(txt);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("He was indeed a deplorable spectacle. In the\n"
            "dim light of a foggy November day the sick room\n"
            "was a gloomy spot, but it was that gaunt, wasted\n"
            "face staring at me from the bed which sent a chill\n"
            "to my heart. His eyes had the brightness of fever,\n"
            "there was a hectic flush upon either cheek, and dark\n"
            "crusts clung to his lips; the thin hands upon the\n"
            "coverlet twitched incessantly, his voice was croaking and spasmodic. He lay listlessly as I entered\n"
            "the room, but the sight of me brought a gleam of\n"
            "recognition to his eyes.\n"
            "“Well, Watson, we seem to have fallen upon evil\n"
            "days,” said he in a feeble voice, but with something\n"
            "of his old carelessness of manner.|\n", output);

    remove_all(txt);
}

// позитивный. текст со множеством пустых строк
TEST(test_shownonempty, positive_2) {
    text txt = create_text();
    load(txt, input_text_with_empty_lines);
    
    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStdout();
    shownonempty(txt);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("He was indeed a deplorable spectacle. In the\n"
            "dim light of a foggy November day the sick room\n"
            "was a gloomy spot, but it was that gaunt, wasted\n"
            "face staring at me from the bed which sent a chill\n"
            "to my heart. His eyes had the brightness of fever,\n"
            "there was a hectic flush upon either cheek, and dark\n"
            "crusts clung to his lips; the thin hands upon the\n"
            "coverlet twitched incessantly, his voice was croaking and spasmodic. He lay listlessly as I entered\n"
            "the room, but the sight of me brought a gleam of\n"
            "recognition to his eyes.\n"
            "“Well, Watson, we seem to have fallen upon evil\n"
            "days,” said he in a feeble voice, but with something\n"
            "of his old carelessness of manner.|\n", output);

    remove_all(txt);
}

// негативный. запуск текста без пустых строк
TEST(test_shownonempty, positive_3) {
    text txt = create_text();
    load(txt, input_non_empty);

    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStdout();
    shownonempty(txt);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("He was indeed a deplorable spectacle. In the\n"
            "dim light of a foggy November day the sick room\n"
            "was a gloomy spot, but it was that gaunt, wasted\n"
            "face staring at me from the bed which sent a chill\n"
            "to my heart. His eyes had the brightness of fever,\n"
            "there was a hectic flush upon either cheek, and dark\n"
            "crusts clung to his lips; the thin hands upon the\n"
            "coverlet twitched incessantly, his voice was croaking and spasmodic. He lay listlessly as I entered\n"
            "the room, but the sight of me brought a gleam of\n"
            "recognition to his eyes.\n"
            "“Well, Watson, we seem to have fallen upon evil\n"
            "days,” said he in a feeble voice, but with something\n"
            "of his old carelessness of manner.|\n", output);

    remove_all(txt);
}

// негативный. не указано имя файла
TEST(test_shownonempty, negative_1) {
    text txt = create_text();
    
    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStdout();
    shownonempty(txt);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("", output);

    remove_all(txt);
}

// негативный. показ пустого текста
TEST(test_shownonempty, negative_2) {
    text txt = create_text();
    load(txt, input_empty);
    
    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStderr();
    shownonempty(txt);
    std::string output = testing::internal::GetCapturedStderr();

    ASSERT_EQ("There are already no any lines in the text!\n", output);

    remove_all(txt);
}

#endif // EQTEST_SNE_H