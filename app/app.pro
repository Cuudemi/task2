TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += editor.c \
    load.c \
    move.c \
    save.c \
    show.c \
    shownonempty.c \
    append_line.c \
    create_text.c \
    process_forward.c \
    remove_all.c \
    rc.c \
    mwbb.c \

HEADERS += \
    common.h \
    _text.h \
    text.h

QMAKE_CFLAGS += -Wall -Wextra

# gcov
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov 
