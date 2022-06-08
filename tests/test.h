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
char *input_text_c = INPUTDIR "/text.c";
char *input_text_with_empty_lines = INPUTDIR "/t.txt";
char *input_empty = INPUTDIR "/empty.txt";
char *input_non_empty = INPUTDIR "/non_empty.txt";
char *input_two_space = INPUTDIR "/2.txt";

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

// негативный. перемещение по пустому тексту
TEST(test_move, negative_5) {
    text txt = create_text();
    load(txt, input_empty);

    move(txt,0, 0);
    
    // захватываем stdout с помощью функции Googletest
    testing::internal::CaptureStderr();
    show(txt);
    std::string output = testing::internal::GetCapturedStderr();

    ASSERT_EQ("There are already no any lines in the text!\n", output);

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

/* -------------------------- rc.c -------------------------- */

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

/* -------------------------- mwbb.c -------------------------- */

// позитивный. загрузка файла, перемещение в начало слова
TEST(test_mwbb, positive_1) {
    text txt = create_text();
    load(txt, input_text);

    move(txt,6,8);
    mwbb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("He was indeed a deplorable spectacle. In the\n"
        "dim light of a foggy November day the sick room\n"
        "was a gloomy spot, but it was that gaunt, wasted\n"
        "face staring at me from the bed which sent a chill\n"
        "to my heart. His eyes had the brightness of fever,\n"
        "there was a hectic flush upon either cheek, and dark\n"
        "crusts |clung to his lips; the thin hands upon the\n"
        "coverlet twitched incessantly, his voice was croaking and spasmodic. He lay listlessly as I entered\n"
        "the room, but the sight of me brought a gleam of\n"
        "recognition to his eyes.\n\n"

        "“Well, Watson, we seem to have fallen upon evil\n"
        "days,” said he in a feeble voice, but with something\n"
        "of his old carelessness of manner.\n", output);

    remove_all(txt);
}

// позитивный. курсор уже находится в начале слова
TEST(test_mwbb, positive_2) {
    text txt = create_text();
    load(txt, input_text);

    move(txt,6,7);
    mwbb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("He was indeed a deplorable spectacle. In the\n"
        "dim light of a foggy November day the sick room\n"
        "was a gloomy spot, but it was that gaunt, wasted\n"
        "face staring at me from the bed which sent a chill\n"
        "to my heart. His eyes had the brightness of fever,\n"
        "there was a hectic flush upon either cheek, and dark\n"
        "crusts |clung to his lips; the thin hands upon the\n"
        "coverlet twitched incessantly, his voice was croaking and spasmodic. He lay listlessly as I entered\n"
        "the room, but the sight of me brought a gleam of\n"
        "recognition to his eyes.\n\n"

        "“Well, Watson, we seem to have fallen upon evil\n"
        "days,” said he in a feeble voice, but with something\n"
        "of his old carelessness of manner.\n", output);

    remove_all(txt);
}

// позитивный. курсор находится в позиции между двумя пробелами
TEST(test_mwbb, positive_3) {
    text txt = create_text();
    load(txt, input_two_space);

    move(txt,5,19);
    mwbb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("He was indeed a deplorable spectacle. In the\n"
        "dim light of a foggy November day the sick room\n"
        "was a gloomy spot, but it was that gaunt, wasted\n"
        "face staring at me from the bed which sent a chill\n"
        "to my heart. His eyes had the brightness of fever,\n"
        "there was a hectic | flush upon either cheek, and dark\n"
        "crusts clung to his lips; the thin hands upon the\n"
        "coverlet twitched incessantly, his voice was croaking and spasmodic. He lay listlessly as I entered\n"
        "the room, but the sight of me brought a gleam of\n"
        "recognition to his eyes.\n\n"

        "“Well, Watson, we seem to have fallen upon evil\n"
        "days,” said he in a feeble voice, but with something\n"
        "of his old carelessness of manner.\n", output);

    remove_all(txt);
}

// негативный. загрузка пустого файла
TEST(test_mwbb, negative_2) {
    text txt = create_text();
    load(txt, input_empty);

    move(txt,0,0);

    testing::internal::CaptureStderr();
    mwbb(txt);
    std::string output = testing::internal::GetCapturedStderr();

    ASSERT_EQ("There are already no any lines in the text!\n", output);

    remove_all(txt);
}
#endif // EQTEST_H