#include <QApplication>
#include <QtCore>
#include "Othello.h"

int main(int argc, char *argv[])
{
 QApplication app(argc, argv);

 reversi Projeto;
 Projeto.show();

 return app.exec();
}
