#ifndef EQTEST_SAVE_H
#define EQTEST_SAVE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <iostream>
#include <fstream>

extern "C" {
#include "common.h"
#include "_text.h"
#include "text.h"
}

// позитивный. загрузка, добавление строки, сохранение
TEST(test_save, positive_1) {
    text txt = create_text();
    load(txt, input_text);
    append_line(txt, "Some text.");

    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStdout();
    save (txt, "text_2.txt");
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("Save file successeed!\n", output);

    remove_all(txt);
}

// негативный. сохранение файла без указания нового имени
TEST(test_save, negative_1) {
    text txt = create_text();
    load(txt, input_text);
    append_line(txt, "Some text.");

    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStdout();
    save (NULL, "text2.txt");
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("", output);

    remove_all(txt);
}

// негативный. сохранение файла в неверный формат
TEST(test_save, negative_2) {
    text txt = create_text();
    load(txt, input_text);
    append_line(txt, input_text);

    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStdout();
    save (NULL, "some.txt");
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("", output);

    remove_all(txt);
}

// негативный. сохранение пустого файла
TEST(test_save, negative_3) {
    text txt = create_text();
    load(txt, input_empty);

    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStderr();
    save (txt, "some.txt");
    std::string output = testing::internal::GetCapturedStderr();

    ASSERT_EQ("The text doesn't exist\n", output);

    remove_all(txt);
}

#endif // EQTEST_SAVE_H