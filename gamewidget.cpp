#include "gamewidget.h"
#include "ui_gamewidget.h"
#include <QIcon>
#include<QSound>
#include<QPixmap>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QBoxLayout>
#include<hero.h>
#include<enemy.h>
#include<global.h>
#include<normalbullet.h>

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    //QHBoxLayout *to = new QHBoxLayout;
    //to->addWidget(ui->Tip);
    //to->addStretch();
    //to->addWidget(ui->soun);
    //QVBoxLayout *al = new QVBoxLayout;
    //al->addLayout(to);
    //al->addStretch();
    //al->addWidget(ui->title);
    //al->addWidget(ui->start);
    //QVBoxLayout *all = new QVBoxLayout;
    //all->addWidget(ui->back);
    //all->addLayout(al);
    //all->addLayout(this->layout());
    //setLayout(all);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    setFixedSize(this->width(), this->height());
    setWindowTitle("Plan fight!");
    setWindowIcon(QIcon(":/res/can.ico"));
    backsound = new QSound(":/res/bac.wav", this);
    backsound->play();
    soundStatu = true;
    LoadMeau();
    update();
    ui->tip->installEventFilter(this);
    ui->start->installEventFilter(this);
    ui->background_label->installEventFilter(this);
    ui->titele->installEventFilter(this);
    ui->sound->installEventFilter(this);
}

void GameWidget::LoadMeau(){
    background = new QImage;
    ui->background_label->setScaledContents(true);
    background->load(":/res/bejin.jpg");
    ui->background_label->setPixmap(QPixmap::fromImage(*background));
    tip = new QImage;
    ui->tip->setScaledContents(true);
    tip->load(":/res/tip.jpg");
    ui->tip->setPixmap(QPixmap::fromImage(*tip));
    start = new QImage;
    ui->start->setScaledContents(true);
    start->load(":/res/begin.jpg");
    ui->start->setPixmap(QPixmap::fromImage(*start));
    sound = new QImage;
    ui->sound->setScaledContents(true);
    sound->load(":/res/sound.jpg");
    ui->sound->setPixmap(QPixmap::fromImage(*sound));
    title = new QImage;
    ui->titele->setScaledContents(true);
    title->load(":/res/title.jpg");
    ui->titele->setPixmap(QPixmap::fromImage(*title));
}

void GameWidget::Gamebegin(){
    ui->background_label->clear();
    ui->background_label->removeEventFilter(this);
    ui->start->clear();
    ui->start->removeEventFilter(this);
    ui->tip->clear();
    ui->tip->removeEventFilter(this);
    ui->titele->clear();
    ui->titele->removeEventFilter(this);
    ui->sound->clear();
    ui->sound->removeEventFilter(this);
    Play();
}

int GameWidget::ExitGame(){
    delete background;
    delete tip;
    delete start;
    delete sound;
    delete title;
    exit(0);
}

void GameWidget::Play(){
    repaint();
    hero *Ownplan;
    enemy *Fish;
    normalbullet *Bullet;
    Ownplan->init(1, 2);
    Fish->init(1, 2);
    Ownplan->init(1, 2);


}

void GameWidget::timerEvent(QTimerEvent *t){


}

bool GameWidget::eventFilter(QObject *obj, QEvent *ev){
    if(obj == ui->Start && ev->type() == QEvent::MouseButtonPress)
        Gamebegin();
    else if (obj == ui->soun && ev->type() == QEvent::MouseButtonPress) {
        if(soundStatu){
            backsound->stop();
            soundStatu = false;
        }
        else {
            backsound->play();
            soundStatu = true;
        }
    }
    else if(obj == ui->tip && ev->type() == QEvent::MouseButtonPress){
        ui->tip->clear();
        ui->start->clear();
        ui->titele->clear();
        ui->sound->clear();
    }
    //else if (obj == ui->tippage) {
    //
    //}

    return QWidget::eventFilter(obj, ev);
}

void GameWidget::paintEvent(QPaintEvent *){
    ui->background_label->resize(ui->back->size());
    ui->tip->resize(ui->Tip->size());
    ui->start->resize(ui->Start->size());
    ui->sound->resize(ui->soun->size());
    ui->titele->resize(ui->title->size());
}

GameWidget::~GameWidget()
{
    delete ui;
}

