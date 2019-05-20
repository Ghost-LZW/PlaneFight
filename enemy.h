#ifndef ENEMY_H
#define ENEMY_H

#include<global.h>
#include<plan.h>

class enemy : public plan {
public:
    enemy();
    ~enemy();

    void add(int x, int y);
};

#endif // ENEMY_H
