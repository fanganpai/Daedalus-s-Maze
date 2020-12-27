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
    player.setX(L.x()/20);
    player.setY(L.y()/20);

    QPainter P(Pix);
    P.setPen(Qt::white);
    P.setBrush(Qt::white);
    float r = 6.5;
    int d = 2*r;
    float line = 8.5;
    //清理影子
    switch (flag)
    {
    case 0://Up
        P.drawEllipse(L.x()-r,   L.y()-r+20,d,d);
        break;
    case 1://Left
        P.drawEllipse(L.x()-r+20, L.y()-r,  d,d);
        break;
    case 2://Down
        P.drawEllipse(L.x()-r,   L.y()-r-20,d,d);
        break;
    case 3://Right
        P.drawEllipse(L.x()-r-20, L.y()-r,  d,d);
        break;
    default:
        break;
    }
    //画棋盘，修复被圆碰坏的部分
    P.setPen(QPen(Qt::gray,2));
    P.setBrush(Qt::white);
    P.drawRect(L.x()/20*20,L.y()/20*20,20,20);
    P.setPen(QPen(Qt::white,2));
    for(int i = L.x()/20-2;i <= L.x()/20+2;i++)
    {
        for (int j = L.y()/20-2; j <= L.y()/20+2;j++)
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
        P.drawPoint(L.x(),L.y()+line);
        break;
    case 1://Left
        P.drawPoint(L.x()+line,L.y());
        break;
    case 2://Down
        P.drawPoint(L.x(),L.y()-line);
        break;
    case 3://Right
        P.drawPoint(L.x()-line,L.y());
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
    QMessageBox::about(this,"Ariadne's Thread","victory!");
}

std::vector<QPair<int,int> > A_algo(QPair<bool,bool> M[40][30],int x,int y);
void MainWindow::cheet()
{
    auto route = A_algo(this->M,player.x(),player.y());
    for (auto i:route)
    {
        auto x = i.first*20 + 10;
        auto y = i.second*20+ 10;
        QPainter P(Pix);
        P.setPen(Qt::gray);
        P.setBrush(Qt::gray);
        P.drawEllipse(x,y,5,5);
    }
    return;
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
    case Qt::Key_W:
        emit tryup();
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        emit trydown();
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        emit tryleft();
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        emit tryright();
        break;
    case Qt::Key_H:
        emit help();
        break;
    default:
        break;
    }
}
