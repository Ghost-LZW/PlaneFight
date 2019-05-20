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
#include<windows.h>

hero *Ownplan;
enemy *Fish;
normalbullet *Bull;

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
    normalbullet *Bull;
    Ownplan = new hero;
    Ownplan->init(0, GAMEHIGHT / 2);
    Fish = new enemy;
    Bull = new normalbullet;
    this->Heropic = Ownplan->PlanImage;
    this->Enemypic = Fish->PlanImage;
    this->Bullpic = Bull->BulletPic;
    *this->myplan = Ownplan->Loc;
    EnemyShotID = startTimer(SLOWSHOT);
    EnemyMoveID = startTimer(SLOWSPEED);
    BulletMoveID = startTimer(10);
    GlobalID = startTimer(BOURNTIME);
    MSG msg;

    while(true){
        if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
            if(msg.message == WM_QUIT)
                break;
            else if(msg.message == WM_KEYDOWN) {
                unsigned key = msg.wParam;
                switch (key) {
                case 'A':
                case 'a':
                case 'W':
                case 'w':
                case 'S':
                case 's':
                case 'd':
                case 'D':
                    Ownplan->move(int(key));
                    break;
                case 32:
                case 'j':
                case 'J':
                    Bull->add(int(myplan->plan.x()) + Ownplan->PLANSIZE, int(myplan->plan.y()) + Ownplan->PLANSIZE / 2, Ownplan->my.Attac, 1);
                    break;
                default: break;
                }
            }
            update();
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        /*int lastlevel = Ownplan->my.level;
        Ownplane.level = Ownplane.my.score / 10 + 1;*/

        if(!Fish->check(Ownplan->PLANSIZE, int(myplan->plan.x()), int(myplan->plan.y()))){
            Ownplan = nullptr;
            myplan = nullptr;
            Ownplan->destory();
            while(Fish->cnt)
                Fish->destory(0);
            break;
        }

        if(Bull->check(Ownplan->PLANSIZE, int(myplan->plan.x()), int(myplan->plan.y()), 1)){
            break;
        }

        for(int i = 0; i < Fish->cnt; i++){
            int x = Fish->getinf(i, 0);
            int y = Fish->getinf(i, 1);
            if(x != -1 && Bull->check(Fish->PLANSIZE, x, y, 0)){
                Fish->destory(i);
                --i;
                Ownplan->socor++;
            }
        }

        if(Ownplan->my.Blood == 0) break;
        update();
    }
    killTimer(EnemyMoveID);
    killTimer(EnemyShotID);
    killTimer(BulletMoveID);
    killTimer(GlobalID);
    char Info[40];
    sprintf(Info, "*你的得分是%d*\n*达到等级%d*", Ownplan->socor, Ownplan->my.level);
    QString buffer(Info);
    QMessageBox::information(this, "GameOver", buffer);
    BackMeau();
}

void GameWidget::timerEvent(QTimerEvent *t){
    srand(time_t(nullptr));
    if(t->timerId() == GlobalID)
    {
        Fish->add(GAMEWIGHT - Fish->PLANSIZE, (rand() % (GAMEHIGHT - Fish->PLANSIZE)), rand() % 10000);
    }
    else if(t->timerId() == EnemyMoveID)
    {
        Fish->move();
    }
    else if(t->timerId() == BulletMoveID)
    {
        Bull->move();
    }
    else if(t->timerId() == EnemyShotID)
    {
        Plan *it = Fish->Phead;
        while(it != nullptr)
        {
            Bull->add(it->plan.x() + it->plan.width() + Bull->BulletSIZE, it->plan.y() + (Fish->PLANSIZE + Bull->BulletSIZE / 2) / 2, 100, 0);
            it = it->next;
        }
    }
    update();
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
    QPainter painter(this);
    if(background == nullptr)return;
    ui->background_label->resize(ui->back->size());
    ui->tip->resize(ui->Tip->size());
    ui->start->resize(ui->Start->size());
    ui->sound->resize(ui->soun->size());
    ui->titele->resize(ui->title->size());
    painter.drawPixmap(0, 0, background->width(), background->height(), QPixmap::fromImage(*background));
    if(this->Heropic == nullptr || this->myplan == nullptr)
        return;
    painter.drawPixmap(myplan->plan.x(), myplan->plan.y(), myplan->plan.width(), myplan->plan.height(), *Heropic);
    if(Enemypic == nullptr)return;
    Plan* enemy = Fish->Phead;
    while (enemy != nullptr) {
        painter.drawPixmap(enemy->plan.x(), enemy->plan.y(), enemy->plan.width(), enemy->plan.height(), *Enemypic);
        enemy = enemy->next;
    }
    if(Bullpic == nullptr)return;
    Bullet *bullet = Bull->head;
    while (bullet != nullptr) {
        painter.drawPixmap(bullet->bull.x(), bullet->bull.y(), bullet->bull.width(), bullet->bull.height(), *Bullpic);
        bullet = bullet->next;
    }

}

GameWidget::~GameWidget()
{
    delete ui;
}

