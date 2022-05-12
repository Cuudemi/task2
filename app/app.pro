TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += editor.c \
    load.c \
    move.c \
    save.c \
    show.c \
    text/append_line.c \
    text/create_text.c \
    text/process_forward.c \
    text/remove_all.c \

HEADERS += \
    common.h \
    text/_text.h \
    text/text.h

QMAKE_CFLAGS += -Wall -Wextra

# gcov
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov 
