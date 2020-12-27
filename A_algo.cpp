#include "unifindmap.h"
#include <vector>
#include <queue>
#include "math.h"
struct myPoint
{
    int x=0,y=0;
    int cost=60000;
    int tcost=0;
    myPoint* Father=nullptr;
    bool operator > (const myPoint &a) const
    {
        return tcost > a.tcost;
    }
};

bool is_moveable(int x1,int y1,int c,QPair<bool,bool> M[40][30])
{
    switch (c)
    {
    case 0://Up
        if(M[x1][y1-1].second)
            return true;
        break;
    case 1://Left
        if(M[x1-1][y1].first)
            return true;
        break;
    case 2://Down
        if(M[x1][y1].second)
            return true;
        break;
    case 3://Right
        if(M[x1][y1].first)
            return true;
        break;
    default:
        break;
    }
    return false;
}

int p_cost(int x1, int y1)
{
    return sqrt((x1-38)*(x1-38) + (y1-28)*(y1-28));
}

std::vector<QPair<int,int> > A_algo(QPair<bool,bool> M[40][30],int x,int y)
{
    bool reach[40][30];
    memset(reach,0,sizeof(reach));
    reach[x][y]=true;

    auto start = new myPoint();
    start->x = x;
    start->y = y;
    start->cost = 0;
    start->tcost = p_cost(x,y) + start->cost;
    std::priority_queue<myPoint*,std::vector<myPoint*>,std::greater<myPoint*> > Q;
    Q.push(start);

    while(!Q.empty())
    {
        auto p = Q.top();
        if (p->x==38 && p->y==28)
        {
            std::vector<QPair<int,int> > route;
            auto t = p;
            while(t!=nullptr)
            {
                route.push_back(QPair<int,int>(t->x,t->y));
                t = t->Father;
            }
            return route;
        }
        Q.pop();
        if(is_moveable(p->x,p->y,0,M) && !reach[p->x][p->y-1]) //Up
        {
            reach[p->x][p->y-1]=true;
            auto newP = new myPoint();
            newP->x=p->x;
            newP->y=p->y -1;
            newP->cost = p->cost + 1;
            newP->tcost = p_cost(newP->x,newP->y) + newP->cost;
            newP->Father = p;
            Q.push(newP);
        }
        if(is_moveable(p->x,p->y,2,M) && !reach[p->x][p->y+1]) //Down
        {
            reach[p->x][p->y+1]=true;
            auto newP = new myPoint();
            newP->x=p->x;
            newP->y=p->y +1;
            newP->cost = p->cost + 1;
            newP->tcost = p_cost(newP->x,newP->y) + newP->cost;
            newP->Father = p;
            Q.push(newP);
        }
        if(is_moveable(p->x,p->y,1,M) && !reach[p->x-1][p->y]) //Left
        {
            reach[p->x-1][p->y]=true;
            auto newP = new myPoint();
            newP->x=p->x -1;
            newP->y=p->y;
            newP->cost = p->cost + 1;
            newP->tcost = p_cost(newP->x,newP->y) + newP->cost;
            newP->Father = p;
            Q.push(newP);
        }
        if(is_moveable(p->x,p->y,3,M) && !reach[p->x+1][p->y]) //Right
        {
            reach[p->x+1][p->y]=true;
            auto newP = new myPoint();
            newP->x=p->x +1;
            newP->y=p->y;
            newP->cost = p->cost + 1;
            newP->tcost = p_cost(newP->x,newP->y) + newP->cost;
            newP->Father = p;
            Q.push(newP);
        }
    }

    return std::vector<QPair<int,int> >();
}
