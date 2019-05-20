#ifndef ZIDAN_H
#define ZIDAN_H
#include<global.h>
class plan;

class bullet{
public:
    bullet();
    virtual ~bullet();

    Bullet *head;
    int xspeed, yspeed, cnt;
    QSound *BulletSound;
    QPixmap *BulletPic;
    int BulletSIZE;
    QString SounLocation = "";
    QString PicLocation = "";
    virtual void init(int harm);
    virtual void move();
    virtual void skill();
    virtual void destory(int k);
    virtual void add(int x, int y, int harm, int fx);
private:

};

#endif // ZIDAN_H
