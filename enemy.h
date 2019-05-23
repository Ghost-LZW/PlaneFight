#ifndef ENEMY_H
#define ENEMY_H

#include<global.h>
#include<plan.h>

class enemy : public plan {
public:
    enemy();
    ~enemy();
    int cnt = 0;
    Plan *Phead = nullptr;
    int vx, vy;
    void add(int x, int y, int blood);
    Plan* init(int x, int y);
    Plan* move();
    Plan* destory(int k);
    bool check(int herosize, int basex, int basey);
    int getinf(int i, int wh);
    void init();
};

#endif // ENEMY_H
