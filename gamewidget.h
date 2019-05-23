#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include<global.h>
#include<QPainter>
#include<hero.h>
#include<enemy.h>
#include<normalbullet.h>
#include<QKeyEvent>

namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget();

private:
    Ui::GameWidget *ui;
    void LoadMeau();
    void Gamebegin();
    void Play();
    int ExitGame();
    void BackMeau();
    hero *Ownplan = nullptr;
    enemy *Fish = nullptr;
    normalbullet *Bull = nullptr;
    QPixmap *Heropic = nullptr;
    QPixmap *Enemypic = nullptr;
    QPixmap *Bullpic = nullptr;
    Plan *myplan = nullptr;
    Plan *Fishhead = nullptr;
    Bullet *bullhead = nullptr;
    QImage *tippage = nullptr;
    QSound *backsound = nullptr;
    QImage *background = nullptr;
    QImage *tip = nullptr;
    QImage *sound = nullptr;
    QImage *title = nullptr;
    QImage *start = nullptr;
    bool pausStatu;
    bool soundStatu;
    int EnemyShotID, EnemyMoveID, BulletMoveID, GlobalID;

protected:
    bool eventFilter(QObject *obj, QEvent *ev);//处理事件
    void timerEvent(QTimerEvent *t);//处理计时器事件
    void paintEvent(QPaintEvent *);//处理画图事件
};

#endif // GAMEWIDGET_H
