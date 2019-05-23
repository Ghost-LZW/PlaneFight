#include "gamewidget.h"
#include "ui_gamewidget.h"
#include <QIcon>
#include<QSound>
#include<QPixmap>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QBoxLayout>
#include<windows.h>
#include <ctime>
#include <cstdlib>
#include <cstring>

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    //setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    setFixedSize(this->width(), this->height());
    setWindowIcon(QIcon(":/res/can.ico"));
    LoadMeau();

    backsound = new QSound(":/res/bac.wav", this);
    backsound->play();
    soundStatu = true;

    update();
    ui->tip->installEventFilter(this);
    ui->start->installEventFilter(this);
    ui->background_label->installEventFilter(this);
    ui->sound->installEventFilter(this);
}

void GameWidget::LoadMeau(){
    background = new QImage;
    background->load(":/res/beijin.png");
    ui->background_label->setPixmap(QPixmap::fromImage(*background));
    tip = new QImage;
    tip->load(":/res/tip.png");
    ui->tip->setPixmap(QPixmap::fromImage(*tip));
    start = new QImage;
    start->load(":/res/begin.png");
    ui->start->setPixmap(QPixmap::fromImage(*start));
    sound = new QImage;
    sound->load(":/res/sound.png");
    ui->sound->setPixmap(QPixmap::fromImage(*sound));
    title = new QImage;
    title->load(":/res/title.png");
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
    ui->sound->clear();
    ui->sound->removeEventFilter(this);
    //background->load(":/res/game.png");
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
    Ownplan = new hero;
    Ownplan->init(10, GAMEHIGHT / 2);
    Fish = new enemy;
    Bull = new normalbullet;
    Bull->init();
    this->Heropic = new QPixmap(QPixmap::fromImage(QImage(Ownplan->PicLocation)));
    this->Enemypic = Fish->PlanImage;
    this->Fishhead = Fish->Phead;
    this->Bullpic = Bull->BulletPic;
    this->bullhead = Bull->Head;
    this->myplan = Ownplan->Loc;
    EnemyShotID = startTimer(SLOWSHOT);
    EnemyMoveID = startTimer(SLOWSPEED);
    BulletMoveID = startTimer(20);
    GlobalID = startTimer(BOURNTIME);
    MSG msg;
    //Bull->move();
    while(true){
        //qDebug() << "循环开始";
        //qDebug()<< "4";
        //Bull->ask();
        if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
            if(msg.message == WM_QUIT)
                break;
            else if(msg.message == WM_KEYDOWN) {
                unsigned long long key = msg.wParam;
                if(msg.wParam == 81 || msg.wParam == 113)break;
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
                case ' ':
                case 'j':
                case 'J':
                    bullhead = Bull->add(int(myplan->plan.x()) + Ownplan->PLANSIZE, int(myplan->plan.y()) + Ownplan->PLANSIZE / 2, Ownplan->my.Attac, 1);
                    break;
                default: break;
                }
            }
            //qDebug() << "use it" << msg.wParam;
            update();
            TranslateMessage(&msg);
            //qDebug() << "5";
            //Bull->ask();
            DispatchMessage(&msg);
            //qDebug() << "6";
            //Bull->ask();
        }
        //qDebug()<< "1";
        //Bull->ask();
        /*int lastlevel = Ownplan->my.level;
        Ownplane.level = Ownplane.my.score / 10 + 1;*/
        //qDebug() << "or here";
        if(!Fish->check(Ownplan->PLANSIZE, int(myplan->plan.x()), int(myplan->plan.y()))){
            myplan = nullptr;
            Ownplan->destory();
            while(Fish->cnt)
                Fish->destory(0);
            break;
        }
        if(!Bull->check(Ownplan->PLANSIZE, int(myplan->plan.x()), int(myplan->plan.y()), 1)){
            Ownplan->my.Blood -= Fish->my.Attac;
        }
        for(int i = 0; i < Fish->cnt; i++){
            int x = Fish->getinf(i, 0);
            int y = Fish->getinf(i, 1);
            if(x != -1 && !Bull->check(Fish->PLANSIZE, x, y, 0)){
                Fishhead = Fish->destory(i);
                --i;
                Ownplan->socor++;
            }
        }
        if(Ownplan->my.Blood == 0) break;
        this->update();
    }
    killTimer(EnemyMoveID);
    killTimer(EnemyShotID);
    killTimer(BulletMoveID);
    killTimer(GlobalID);
    char Info[40];
    sprintf(Info, "Socor: %d\nlevel: %d", Ownplan->socor, Ownplan->my.level);
    QString buffer(Info);
    QMessageBox::information(this, "GameOver", buffer);
    BackMeau();
}

void GameWidget::BackMeau(){
    //background->load(":/res/beijin.png");
    ui->background_label->setPixmap(QPixmap::fromImage(*background));
    ui->tip->setPixmap(QPixmap::fromImage(*tip));
    ui->start->setPixmap(QPixmap::fromImage(*start));
    ui->titele->setPixmap(QPixmap::fromImage(*title));
    ui->sound->setPixmap(QPixmap::fromImage(*sound));
    ui->author_label->setText("by :liupo");
    ui->background_label->installEventFilter(this);
    ui->tip->installEventFilter(this);
    ui->start->installEventFilter(this);
    ui->titele->installEventFilter(this);
    ui->sound->installEventFilter(this);
}

void GameWidget::timerEvent(QTimerEvent *t){
    srand(time(nullptr));
    //qDebug() << "time " << t->timerId() << " " << GlobalID << " " << EnemyMoveID << " " << EnemyShotID << " " << BulletMoveID;
    //qDebug()<< "touch it";
    //Bull->ask();
    //if(t->timerId() == 7)qDebug() << "time for me";
    if(t->timerId() == GlobalID){
        Fish->add(GAMEWIGHT - Fish->PLANSIZE  - 10, ((rand() * rand()) % (GAMEHIGHT - Fish->PLANSIZE)), rand() % 10000);
        Fishhead = Fish->Phead;
    }
    else if(t->timerId() == EnemyMoveID){
        Fishhead = this->Fish->move();
    }
    else if(t->timerId() == BulletMoveID){
        bullhead = Bull->move();
    }
    else if(t->timerId() == EnemyShotID){
        Plan *it = Fish->Phead;
        while(it != nullptr){
            bullhead = Bull->add(it->plan.x() - Bull->BulletSIZE, it->plan.y() + (Fish->PLANSIZE + Bull->BulletSIZE / 2) / 2, 100, 0);
            it = it->next;
        }
    }
    update();
}

bool GameWidget::eventFilter(QObject *obj, QEvent *ev){
    //qDebug() << "error";
    if(obj == ui->start && ev->type() == QEvent::MouseButtonPress)
        Gamebegin();
    else if (obj == ui->sound && ev->type() == QEvent::MouseButtonPress) {
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
    //qDebug() << "test it";
    QPainter painter(this);
    //QPixmap qq(":/res/enemy.png");
    //if(Enemypic != nullptr)painter.drawPixmap(60, 60, qq.width(), qq.height(), *Enemypic);
    if(background == nullptr)return;
    //ui->background_label->resize(ui->back->size());
    //ui->tip->resize(ui->Tip->size());
    //ui->start->resize(ui->Start->size());
    //ui->sound->resize(ui->soun->size());
    //ui->titele->resize(ui->title->size());
    painter.drawPixmap(0, 0, background->width(), background->height(), QPixmap::fromImage(QImage(":/game.png")));
    if(this->Heropic == nullptr || this->myplan == nullptr)
        return;
    painter.drawPixmap(this->myplan->plan.x(), this->myplan->plan.y(), this->Heropic->width(), this->Heropic->height(), *this->Heropic);
    //qDebug() << "planx = " << this->myplan->plan.x() << "plany = " << this->myplan->plan.y();
    //qDebug() << "painter plan";
    if(Enemypic == nullptr)return;
    //qDebug() <<"tset show that " <<(Fishhead == nullptr ? 1 : 0);
    Plan *gw = Fish->Phead;
    //qDebug() << "next step";
    while (gw != nullptr) {
        painter.drawPixmap(gw->plan.x(), gw->plan.y(), this->Enemypic->width(), this->Enemypic->height(), *Enemypic);
        gw = gw->next;
    }
    //qDebug() << "enemy painter";
    if(Bullpic == nullptr)return;
    Bullet *bullet = Bull->Head;
    while (bullet != nullptr) {
        painter.drawPixmap(bullet->bull.x(), bullet->bull.y(), this->Bullpic->width(), this->Bullpic->height(), *Bullpic);
        bullet = bullet->next;
    }
    //qDebug() << "bullt paint";
}

GameWidget::~GameWidget()
{
    delete ui;
}

