#ifndef EQTEST_LOAD_H
#define EQTEST_LOAD_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <iostream>
#include <fstream>

extern "C" {
#include "common.h"
#include "_text.h"
#include "text.h"
}

char *input_text = INPUTDIR "/text.txt";
char *input_text_c = INPUTDIR "/text.c";
char *input_text_with_empty_lines = INPUTDIR "/t.txt";
char *input_empty = INPUTDIR "/empty.txt";
char *input_non_empty = INPUTDIR "/non_empty.txt";
char *input_two_space = INPUTDIR "/2.txt";

// позитивный. загрузка txt файла
TEST(test_load, positive_1) {
    text txt = create_text();

    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStdout();
    load(txt, input_text);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("Load file successeed!\n", output);

    remove_all(txt);
}

// негативный. загрузка отсутсвующего файла
TEST(test_load, negative_1) {
    text txt = create_text();

    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStdout();
    load(txt, "non-existent_file.txt");
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("The file non-existent_file.txt cannot be opened\n", output);

    remove_all(txt);
}

// негативный. загрузка нетекстового файла (картинки jpg)
TEST(test_load, negative_2) {
    text txt = create_text();

    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStdout();
    load(txt, "3.jpg");
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("The file 3.jpg cannot be opened\n", output);

    remove_all(txt);
}

#endif // EQTEST_LOAD_H