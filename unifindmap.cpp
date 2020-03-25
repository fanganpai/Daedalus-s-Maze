#include "unifindmap.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
UnifindMap::UnifindMap(QObject *parent) : QObject(parent)
{
    srand((unsigned)time(NULL));
    size_t y = 1 + rand()%28;
    player = QPoint(20*1+10,20*y+10);
    size_t x = 1 + 37;
    map[1][y] = v_type(1,y);
    map[x][28] = v_type(x,28);
    while (map[0][y]!=map[x][29])
    {
        size_t xt = 1 + rand() % 38;
        size_t yt = 1 + rand() % 28;
        if(map[xt][yt]==map[1][y] || map[xt][yt]==map[x][28])
        {
            switch (rand() % 4)
            {
            case 0:
                if(map[xt+1][yt]==map[xt][yt])
                    break;
                map[xt+1][yt] = v_type(xt+1, yt);
                Union(&map[xt][yt],&map[xt+1][yt]);
                map[xt][yt].down = true;
                break;
            case 1:
                if(map[xt][yt+1]==map[xt][yt])
                    break;
                map[xt][yt+1] = v_type(xt, yt+1);
                Union(&map[xt][yt],&map[xt][yt+1]);
                map[xt][yt].right = true;
                break;
            case 2:
                if(map[xt-1][yt]==map[xt][yt])
                    break;
                map[xt-1][yt] = v_type(xt-1, yt);
                Union(&map[xt][yt],&map[xt-1][yt]);
                map[xt-1][yt].down = true;
                break;
            case 3:
                if(map[xt][yt-1]==map[xt][yt])
                    break;
                map[xt][yt-1] = v_type(xt, yt-1);
                Union(&map[xt][yt],&map[xt][yt-1]);
                map[xt][yt-1].right = true;
            default:
                break;
            }
        }
    }
}

void UnifindMap::Up()
{
    int x = (player.x() - 0) / 20;
    int y = (player.y() - 13) / 20;
    if(y == 0)    return;
    //y = (player.y() - 1 - 7.5) / 20;
    if(player.y()/20==y || map[x][y].right)
    {
        player = QPoint(player.x(),player.y() - 1);
        emit moving(player, 0);
        return;
    }
    return;
}

void UnifindMap::Left()
{
    int x = (player.x() - 13) / 20;
    int y = (player.y() - 0) / 20;
    if(x == 0)    return;
    //x = (player.x() - 1 - 7.5) / 20;
    if(player.x()/20==x || map[x][y].down)
    {
        player = QPoint(player.x() - 1,player.y());
        emit moving(player, 1);
        return;
    }
    return;
}

void UnifindMap::Down()
{
    int x = (player.x() + 0) / 20;
    int y = (player.y() + 13) / 20;
    if(y == 29)    return;
    if(player.y()/20==y || map[x][y-1].right)
    {
        player = QPoint(player.x(),player.y() + 1);
        emit moving(player, 2);
        return;
    }
    return;
}

void UnifindMap::Right()
{
    int x = (player.x() + 13) / 20;
    int y = (player.y() + 0) / 20;
    if(x == 39)
    {
        if(y == 28)
            emit win();
        return;
    }
    if(player.x()/20==x || map[x-1][y].down)
    {
        player = QPoint(player.x() + 1,player.y());
        emit moving(player, 3);
        return;
    }
    return;
}

bool Union(Set *A, Set *B)
{
    if (A == nullptr || B == nullptr)
    {
        return false;
    }
    while (A->father != nullptr)
    {
        A = A->father;
    }
    while (B->father != nullptr)
    {
        B = B->father;
    }
    if (A == B)
        return false;
    auto rankA = A->rank;
    auto rankB = B->rank;
    if (rankA > rankB)
    {
        auto C = B;
        B = A;
        A = C;
    }
    B->father = A;
    A->rank = std::max(rankA,rankB) + rankA == rankB ? 1 : 0;
    return true;
}


bool issame(Set *A, Set *B)
{
    if (A == nullptr || B == nullptr)
    {
        return false;
    }
    while (A->father != nullptr)
    {
        A = A->father;
    }
    while (B->father != nullptr)
    {
        B = B->father;
    }
    return A == B ? 1 : 0;
}
