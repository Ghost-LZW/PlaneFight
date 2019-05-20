#ifndef NORMALBULLET_H
#define NORMALBULLET_H
#include<zidan.h>

class normalbullet : public bullet{
public:
    normalbullet();
    ~normalbullet();

    void destory(int k);
    void move();
    void add(int x, int y, int harm, int fx);
    bool check(int herosize, int basex, int basey, int flag);
};

#endif // NORMALBULLET_H
