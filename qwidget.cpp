#include<QWidget>
#include<gamewidget.h>

void QWidget::paintEvent(QPaintEvent *event){
    GameWidget::paintEvent(event);
}
