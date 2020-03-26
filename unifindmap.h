#ifndef UNIFINDMAP_H
#define UNIFINDMAP_H

#include <QObject>
#include <QPair>
#include <QPoint>
//并查集
using v_type = QPair<size_t,size_t>;
class Set
{
public:
    Set():value(v_type(0,0)){}
    Set(v_type v) : value(v) {}
    Set(v_type v, Set *p) : value(v), father(p) {}
    Set(v_type v, Set &p) : value(v), father(&p) {}
    v_type getvalue() { return value; }
    Set& getroot()
    {
        auto root = this;
        while (root->father != nullptr)
        {
            auto t = root->father;
            root->father = t->father;
            root = t;
        }
        return *root;
    }
    Set& operator+ (Set &B)
    {
        Union(this, &B);
        return this->getroot();
    }
    void operator= (v_type val)
    {
        this->value = val;
    }
    bool operator== (Set &B)
    {
        return issame(this, &B);
    }
    bool operator !=(Set &B)
    {
        return !issame(this, &B);
    }

    v_type value;
    bool right  = false; //这地方是按X垂直向下、Y水平向右的方向写的，和Qt窗口的坐标相反……用的时候记得倒一下
    bool down   = false;
    Set *father = nullptr;
    int rank = 0;
    friend bool Union(Set *A, Set *B);
    friend bool issame(Set *A, Set *B);
};

//并查集地图，负责地图生成和移动判定的逻辑
class UnifindMap : public QObject
{
    Q_OBJECT
public:
    explicit UnifindMap(QObject *parent = nullptr);
    Set map[40][30];
    void run()
    {
        emit initmap(map);
        emit moving(player,0);
    }
private:
    QPoint player = QPoint(30,30);
public slots:
    void Up();
    void Down();
    void Left();
    void Right();
signals:
    void initmap(const Set[][30]);
    void moving(QPoint&, int);
    void win();
};

#endif // UNIFINDMAP_H
