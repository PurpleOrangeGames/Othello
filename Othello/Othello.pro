QT       += core gui sql declarative opengl
DESTDIR = "../bin"
TEMPLATE = app
CONFIG += plugin
HEADERS += Othello.h
SOURCES += Board.cpp \
           Minimax.cpp \
           Othello.cpp \
           main.cpp
RESOURCES += ./othello.qrc

OTHER_FILES += Core/Button.qml\
    Othello.qml \
    Core/List.qml \
    Core/Options.qml \
    Core/qmldir \
    Core/ProgressBar.qml






