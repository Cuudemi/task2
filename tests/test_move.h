#ifndef EQTEST_MOVE_H
#define EQTEST_MOVE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <iostream>
#include <fstream>

extern "C" {
#include "common.h"
#include "_text.h"
#include "text.h"
}

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

#endif // EQTEST_MOVE_H