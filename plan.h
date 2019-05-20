#ifndef PLAN_H
#define PLAN_H
#include<global.h>
#include<string>

class plan {
public:
    plan();
    virtual ~plan();
    struct sx{
        int Blod, Size, Speed, Attac, level;
    }my;

    Plan Loc;
    int PLANSIZE;
    QString PicLocation;

    QSound *PersonBackgroundSound;
    QPixmap *PlanImage;
    plan *head;
    bool gg;
    virtual void skill();
    virtual void init(int x, int y);
    virtual void destory();
    virtual void move(int key);
    virtual void attac();
    virtual void hurt();
    virtual void add(int x, int y, int blood);

private:
};

#endif // PLAN_H
