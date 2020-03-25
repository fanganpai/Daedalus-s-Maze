#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UnifindMap m;
    MainWindow w;
    QObject::connect(&m, &UnifindMap::initmap,  &w, &MainWindow::initMap);
    QObject::connect(&m, &UnifindMap::moving,   &w, &MainWindow::refresh);
    QObject::connect(&w, &MainWindow::tryup,    &m, &UnifindMap::Up);
    QObject::connect(&w, &MainWindow::trydown,  &m, &UnifindMap::Down);
    QObject::connect(&w, &MainWindow::tryleft,  &m, &UnifindMap::Left);
    QObject::connect(&w, &MainWindow::tryright, &m, &UnifindMap::Right);
    QObject::connect(&m, &UnifindMap::win,      &w, &MainWindow::gameover);
    m.run();
    w.show();
    return a.exec();
}
