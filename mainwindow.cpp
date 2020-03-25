#include "mainwindow.h"
#include "ui_mainwindow.h"
const int Win_Wight=800;
const int Win_Height=600;
const char WinTitle[]="Daedalus's Labyrinth";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(Win_Wight,Win_Height);
    setWindowTitle(WinTitle);
    Pix = new QPixmap(Win_Wight,Win_Height);
    Pix->fill(Qt::gray);
}

MainWindow::~MainWindow()
{
    delete Pix;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter P(this);
    P.drawPixmap(0, 0, Win_Wight,Win_Height,*Pix);


}

void MainWindow::refresh(const QPoint &L, int flag)
{
    QPainter P(Pix);
    P.setPen(Qt::white);
    P.setBrush(Qt::white);
    int r = 6.5;
    int d = 2*r;
    //清理影子
    P.drawEllipse(L.x()-r-1, L.y()-r,  d,d);
    P.drawEllipse(L.x()-r+1, L.y()-r,  d,d);
    P.drawEllipse(L.x()-r,   L.y()-r-1,d,d);
    P.drawEllipse(L.x()-r,   L.y()-r+1,d,d);
    //画棋盘，修复被圆碰坏的部分
    P.setPen(QPen(Qt::gray,2));
    P.setBrush(Qt::white);
    P.drawRect(L.x()/20*20,L.y()/20*20,20,20);
    P.setPen(QPen(Qt::white,2));
    for(int i = L.x()/20-1;i <= L.x()/20+1;i++)
    {
        for (int j = L.y()/20-1; j <= L.y()/20+1;j++)
        {
            if(M[i][j].first)
                P.drawLine(QPoint(20*i+20,20*j),QPoint(20*i+20,20*j+20));
            if(M[i][j].second)
                P.drawLine(QPoint(20*i,20*j+20),QPoint(20*i+20,20*j+20));

        }
    }
    //画主角
    P.setPen(Qt::darkRed);
    P.setBrush(Qt::darkRed);
    P.drawEllipse(L.x()-r,L.y()-r,d,d);
    switch (flag)
    {
    case 0://Up
        P.drawPoint(L.x(),L.y()+8.5);
        break;
    case 1://Left
        P.drawPoint(L.x()+8.5,L.y());
        break;
    case 2://Down
        P.drawPoint(L.x(),L.y()-8.5);
        break;
    case 3://Right
        P.drawPoint(L.x()-8.5,L.y());
        break;
    default:
        break;
    }

    this->update();
}
void MainWindow::initMap(const Set map[40][30])
{
    QPainter P(Pix);
    P.setPen(QPen(Qt::white,2));
    P.setBrush(Qt::white);
    for(size_t i = 1;i < 39;i++)
    {
        for (size_t j = 1; j < 29;j++)
        {
            auto loc = map[i][j].value;
            if(loc.first!=0 || loc.second!=0)
            {
                int x = loc.first*20;
                int y = loc.second*20;
                P.drawRect(x+2,y+2,16,16);
                if(map[i][j].down)
                {
                    P.drawLine(QPoint(x+20,y),QPoint(x+20,y+20));
                    M[i][j].first=true;
                }
                if(map[i][j].right)
                {
                    P.drawLine(QPoint(x,y+20),QPoint(x+20,y+20));
                    M[i][j].second=true;
                }
            }
        }
    }
    P.drawRect(39*20,28*20,20,20);
    refresh(QPoint(1,1),0);
}

void MainWindow::gameover()
{
    QMessageBox::about(this,"Ariadne's Thread","锈剑仍可一斩，\n愿她的丝线绵长不断");
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        emit tryup();
        break;
    case Qt::Key_Down:
        emit trydown();
        break;
    case Qt::Key_Left:
        emit tryleft();
        break;
    case Qt::Key_Right:
        emit tryright();
        break;
    default:
        break;
    }
}
