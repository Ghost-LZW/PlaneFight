#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include<global.h>

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
    QImage *tippage;
    QSound *backsound;
    QImage *background;
    QImage *tip;
    QImage *sound;
    QImage *title;
    QImage *start;
    bool pausStatu;
    bool soundStatu;

protected:
    bool eventFilter(QObject *obj, QEvent *ev);//处理事件
    void timerEvent(QTimerEvent *t);//处理计时器事件
    void paintEvent(QPaintEvent *);//处理画图事件
};

#endif // GAMEWIDGET_H
