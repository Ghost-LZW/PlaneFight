#ifndef GLOBAL_H
#define GLOBAL_H
#include<QRect>
#include<QSound>
#include<QImage>
#include<QPixmap>
#include<QMessageBox>
#include <QDebug>

#define MAX_BLOD 10000000
#define MIN_BLOD 0
#define MAX_HARM 10000
#define MIN_HARM 1
#define GAMEHIGHT 540
#define GAMEWIGHT 960
#define SLOWSPEED 500
#define SLOWSHOT 1200
#define BOURNTIME 1500

struct Plan{
    QRect plan;
    int Blood;
    Plan *next;
};

struct Bullet{
    QRect bull;
    int harm;
    int fx;
    Bullet* next;
};

#endif // GLOBAL_H
