#ifndef NORMALBULLET_H
#define NORMALBULLET_H
#include<global.h>

class normalbullet{
public:
    normalbullet();
    ~normalbullet();

    int xspeed, yspeed, cnt;
    QSound *BulletSound = nullptr;
    QPixmap *BulletPic = nullptr;
    int BulletSIZE;
    QString SounLocation = "";
    QString PicLocation = "";
    void init();

    void ask();
    Bullet* destory(int k);
    Bullet* move();
    Bullet* gethead();
    Bullet* add(int x, int y, int harm, int fx);
    bool check(int herosize, int basex, int basey, int flag);
    Bullet* Head;
protected:

};

#endif // NORMALBULLET_H
