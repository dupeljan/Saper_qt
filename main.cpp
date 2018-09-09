#include "mainwindow.h"
#include "playground.h"
#include "game.h"
#include "dialog.h"
#include <QApplication>
#include <QWidget>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // QWidget *window = new QWidget;
    game *x = new game(10,10,5);
    Dialog *window = new Dialog(0,x);
    window->show();
    //window->setLayout(x->getLayout());
    //window->show();
    //MainWindow w;
    //w.show();

    return a.exec();
}
