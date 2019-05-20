#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include<global.h>
#include<QPainter>

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
    QPixmap *Heropic;
    QPixmap *Enemypic;
    QPixmap *Bullpic;
    Plan *myplan;
    QImage *tippage;
    QSound *backsound;
    QImage *background;
    QImage *tip;
    QImage *sound;
    QImage *title;
    QImage *start;
    bool pausStatu;
    bool soundStatu;
    int EnemyShotID, EnemyMoveID, BulletMoveID, GlobalID;

protected:
    bool eventFilter(QObject *obj, QEvent *ev);//处理事件
    void timerEvent(QTimerEvent *t);//处理计时器事件
    void paintEvent(QPaintEvent *);//处理画图事件
};

#endif // GAMEWIDGET_H
