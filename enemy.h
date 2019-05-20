#ifndef ENEMY_H
#define ENEMY_H

#include<global.h>
#include<plan.h>

class enemy : public plan {
public:
    enemy();
    ~enemy();
    int cnt = 0;
    int vx, vy;
    void add(int x, int y, int blood);
    void init(int x, int y);
    void move();
    void destory(int k);
    bool check(int herosize, int basex, int basey);
    int getinf(int i, int wh);
};

#endif // ENEMY_H
