#ifndef GLOBAL_H
#define GLOBAL_H
#include<QRectF>
#include<QSound>
#include<QImage>
#include<QPixmap>

#define MAX_BLOD 10000000
#define MIN_BLOD 0
#define MAX_HARM 10000
#define MIN_HARM 1
#define GAMEHIGHT 540
#define GAMEWIGHT 960

struct Plan{
    QRectF plan;
    Plan *next;
};

struct Bullet{
    QRectF bull;
    int harm;
    Bullet* next;
};

#endif // GLOBAL_H
