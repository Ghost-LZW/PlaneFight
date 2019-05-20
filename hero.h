#ifndef HERO_H
#define HERO_H
#include<global.h>
#include<plan.h>

class hero : public plan{
public:
     hero();
    ~hero();

     void move(int k);
};

#endif // HERO_H
