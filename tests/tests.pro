include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CFLAGS += -Wall -Wextra

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

DEFINES += INPUTDIR=\\\"$$PWD/input/\\\"

HEADERS += tests.h \
        ../app/common.h \
        ../app/text.h \
        ../app/_text.h

SOURCES +=     main.cpp \
    ../app/load.c \
    ../app/move.c \
    ../app/save.c \
    ../app/show.c \
    ../app/shownonempty.c \
    ../app/append_line.c \
    ../app/create_text.c \
    ../app/process_forward.c \
    ../app/remove_all.c

INCLUDEPATH += ../app

DISTFILES += \
    input/text.txt \
    tests/input/text.txt
