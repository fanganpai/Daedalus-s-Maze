#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPair>
#include <QPainter>
#include <QPixmap>
#include <QX11Info>
#include <QKeyEvent>
#include <QMessageBox>
#include "unifindmap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//主窗口，完成绘图
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
public slots:
    void initMap(const Set[][30]);
    void refresh(const QPoint&,int);
    void gameover();
    void cheet();
signals:
    void tryup();
    void trydown();
    void tryleft();
    void tryright();
    void help();
private:
    Ui::MainWindow *ui;
    QPushButton *m_button;
    QPixmap *Pix;
    QPair<bool,bool> M[40][30];
    QPoint player = QPoint(1,1);
};
#endif // MAINWINDOW_H
