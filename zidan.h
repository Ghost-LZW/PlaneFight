#ifndef ZIDAN_H
#define ZIDAN_H
#include<global.h>
class plan;

class bullet{
public:
    bullet();
    ~bullet();
    struct sx{
        int Harm;
    };

    int xspeed, yspeed;
    QSound *BulletSound;
    QImage *BulletPic;
    bullet *head;
    virtual void init(int harm);
    virtual void move();
    virtual void skill();
    virtual void add(int x, int y, int harm);
private:

};

#endif // ZIDAN_H
