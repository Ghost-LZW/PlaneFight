#ifndef HERO_H
#define HERO_H
#include<global.h>
#include<plan.h>

class hero : public plan{
public:
     hero();
    ~hero();

     int socor;
     void move(int k);
     void init(int x, int y);
};

#endif // HERO_H
