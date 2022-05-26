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

char *input_text = INPUTDIR "/text.txt";
char *input_text_with_empty_lines = INPUTDIR "/t.txt";

/* -------------------------- move.c -------------------------- */

// позитивный. первая строка, начало первого слова
TEST(test_move, positive_1) {
    text txt = create_text();
    load(txt, input_text);

    move(txt,0,0);
    
    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("|He was indeed a deplorable spectacle. In the\n"
            "dim light of a foggy November day the sick room\n"
            "was a gloomy spot, but it was that gaunt, wasted\n"
            "face staring at me from the bed which sent a chill\n"
            "to my heart. His eyes had the brightness of fever,\n"
            "there was a hectic flush upon either cheek, and dark\n"
            "crusts clung to his lips; the thin hands upon the\n"
            "coverlet twitched incessantly, his voice was croaking and spasmodic. He lay listlessly as I entered\n"
            "the room, but the sight of me brought a gleam of\n"
            "recognition to his eyes.\n\n"

            "“Well, Watson, we seem to have fallen upon evil\n"
            "days,” said he in a feeble voice, but with something\n"
            "of his old carelessness of manner.\n", output);

    remove_all(txt);
}

// позитивный. 4 строка, конец второго слова
TEST(test_move, positive_2) {
    text txt = create_text();
    load(txt, input_text);

    move(txt,3,12);
    
    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("He was indeed a deplorable spectacle. In the\n"
            "dim light of a foggy November day the sick room\n"
            "was a gloomy spot, but it was that gaunt, wasted\n"
            "face staring| at me from the bed which sent a chill\n"
            "to my heart. His eyes had the brightness of fever,\n"
            "there was a hectic flush upon either cheek, and dark\n"
            "crusts clung to his lips; the thin hands upon the\n"
            "coverlet twitched incessantly, his voice was croaking and spasmodic. He lay listlessly as I entered\n"
            "the room, but the sight of me brought a gleam of\n"
            "recognition to his eyes.\n\n"

            "“Well, Watson, we seem to have fallen upon evil\n"
            "days,” said he in a feeble voice, but with something\n"
            "of his old carelessness of manner.\n", output);

    remove_all(txt);
}

// позитивный. конец последнего слова
TEST(test_move, positive_3) {
    text txt = create_text();
    load(txt, input_text);

    move(txt,13,33);
    
    testing::internal::CaptureStdout();
    show(txt);
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
            "recognition to his eyes.\n\n"

            "“Well, Watson, we seem to have fallen upon evil\n"
            "days,” said he in a feeble voice, but with something\n"
            "of his old carelessness of manner|.\n", output);

    remove_all(txt);
}

// негативный. выход за пределы текста вверх
TEST(test_move, negative_1) {
    text txt = create_text();
    load(txt, input_text);

    move(txt,-10, 0);
    
    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("|He was indeed a deplorable spectacle. In the\n"
            "dim light of a foggy November day the sick room\n"
            "was a gloomy spot, but it was that gaunt, wasted\n"
            "face staring at me from the bed which sent a chill\n"
            "to my heart. His eyes had the brightness of fever,\n"
            "there was a hectic flush upon either cheek, and dark\n"
            "crusts clung to his lips; the thin hands upon the\n"
            "coverlet twitched incessantly, his voice was croaking and spasmodic. He lay listlessly as I entered\n"
            "the room, but the sight of me brought a gleam of\n"
            "recognition to his eyes.\n\n"

            "“Well, Watson, we seem to have fallen upon evil\n"
            "days,” said he in a feeble voice, but with something\n"
            "of his old carelessness of manner.\n", output);

    remove_all(txt);
}

// негативный. выход за пределы текста вниз
TEST(test_move, negative_2) {
    text txt = create_text();
    load(txt, input_text);

    move(txt,123, 0);
    
    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStdout();
    show(txt);
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
            "recognition to his eyes.\n\n"

            "“Well, Watson, we seem to have fallen upon evil\n"
            "days,” said he in a feeble voice, but with something\n"
            "|of his old carelessness of manner.\n", output);

    remove_all(txt);
}

// негативный. выход за пределы текста вправо
TEST(test_move, negative_3) {
    text txt = create_text();
    load(txt, input_text);

    move(txt,0, 123);
    
    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("He was indeed a deplorable spectacle. In the|\n"
            "dim light of a foggy November day the sick room\n"
            "was a gloomy spot, but it was that gaunt, wasted\n"
            "face staring at me from the bed which sent a chill\n"
            "to my heart. His eyes had the brightness of fever,\n"
            "there was a hectic flush upon either cheek, and dark\n"
            "crusts clung to his lips; the thin hands upon the\n"
            "coverlet twitched incessantly, his voice was croaking and spasmodic. He lay listlessly as I entered\n"
            "the room, but the sight of me brought a gleam of\n"
            "recognition to his eyes.\n\n"

            "“Well, Watson, we seem to have fallen upon evil\n"
            "days,” said he in a feeble voice, but with something\n"
            "of his old carelessness of manner.\n", output);

    remove_all(txt);
}

// негативный. выход за пределы текста влево
TEST(test_move, negative_4) {
    text txt = create_text();
    load(txt, input_text);

    move(txt,0, -10);
    
    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("|He was indeed a deplorable spectacle. In the\n"
            "dim light of a foggy November day the sick room\n"
            "was a gloomy spot, but it was that gaunt, wasted\n"
            "face staring at me from the bed which sent a chill\n"
            "to my heart. His eyes had the brightness of fever,\n"
            "there was a hectic flush upon either cheek, and dark\n"
            "crusts clung to his lips; the thin hands upon the\n"
            "coverlet twitched incessantly, his voice was croaking and spasmodic. He lay listlessly as I entered\n"
            "the room, but the sight of me brought a gleam of\n"
            "recognition to his eyes.\n\n"

            "“Well, Watson, we seem to have fallen upon evil\n"
            "days,” said he in a feeble voice, but with something\n"
            "of his old carelessness of manner.\n", output);

    remove_all(txt);
}


/* -------------------------- load.c -------------------------- */

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


/* -------------------------- save.c -------------------------- */

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
    save (txt, NULL);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("", output);

    remove_all(txt);
}



/* -------------------------- shownonempty.c -------------------------- */

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

#endif // EQTEST_H