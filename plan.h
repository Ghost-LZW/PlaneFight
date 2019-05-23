#ifndef PLAN_H
#define PLAN_H
#include<global.h>
#include<string>

class plan {
public:
    plan();
    virtual ~plan();
    struct sx{
        int Blood, Speed, Attac, level;
    }my;

    Plan* Loc;
    QString PicLocation;

    int PLANSIZE;
    QSound *PersonBackgroundSound;
    QPixmap *PlanImage;
    plan *head;
    bool gg;
    //virtual void skill();
    void init(int x, int y);
    void destory();
    void move(int key);
    //virtual void attac();
    //virtual void hurt();
    //void add(int x, int y, int blood);

private:
};

#endif // PLAN_H
