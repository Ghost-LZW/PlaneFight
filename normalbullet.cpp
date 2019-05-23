#include<normalbullet.h>
#include<QSound>

normalbullet::normalbullet(){

}

void normalbullet::init(){
    PicLocation = ":/res/bulllet.png";
    BulletPic = new QPixmap;
    BulletPic->load(PicLocation);
    //BulletSound = new QSound(SounLocation);
    BulletSIZE = 5;
    Head = nullptr;

    cnt = 0;
    xspeed = 20;
    yspeed = 1;
}

void normalbullet::ask(){
    qDebug() << "see here";
    if(Head == nullptr)qDebug() << "wroong";
}

normalbullet::~normalbullet(){
    delete BulletPic;
    delete BulletSound;
}

Bullet *normalbullet::add(int x, int y, int harm, int fx){
     Bullet *it;
     it = new Bullet;
     it->fx = fx;
     it->harm = harm;
     it->bull.setX(x);
     it->bull.setY(y);
     it->bull.setWidth(BulletSIZE);
     it->bull.setHeight(BulletSIZE);
     it->next = nullptr;
     if(Head == nullptr){
         Head = it;
     }
     else {
         it->next = Head;
         Head = it;
     }
     cnt++;
     return  Head;
}

bool normalbullet::check(int herosize, int basex, int basey, int flag){
     Bullet *it = Head;
     flag = !flag;
     int i = 0;
     while(it != nullptr){
         Bullet *temp = it->next;
         if(it->fx == flag){
             if(it->bull.x() >= basex && it->bull.x() < basex + herosize && it->bull.y() > basey && it->bull.y() <= basey + herosize){
                 destory(i);
                 i--;
                 return false;
             }
         }
         it = temp;
     }
     return true;
}

Bullet* normalbullet::destory(int k){
    Bullet *it = Head;
    if(k == 0){
        Head = Head->next;
        delete it;
    }
    else{
    for(int i = 0; i < k - 1; i++)
        it = it->next;
    Bullet *temp = it->next;
    it->next = temp->next;
    delete temp;
    }
    --cnt;
    return Head;
}

Bullet* normalbullet::move(){
    //Head = Q_NULLPTR;
    //if(Head == NULL)qDebug() << "error";
    //Head = new Bullet;
    //qDebug() << "am i ";
    Bullet* it = Head;
    //qDebug() << "dead??";
    //if(Head != NULL)it = Head;
    //qDebug() << "now ?";
    int i = 0;
    while (it != nullptr) {
        it->bull.setX(it->bull.x() + (it->fx ? xspeed : -xspeed));
        it->bull.setY(it->bull.y() + yspeed);
        it->bull.setWidth(BulletSIZE);
        it->bull.setHeight(BulletSIZE);
        Bullet *temp = it->next;
        if(it->bull.x() < 0 || it->bull.x() + BulletSIZE > GAMEWIGHT ||it->bull.y() < 0 || it->bull.y() + BulletSIZE > GAMEHIGHT){
            destory(i);
            i--;
            cnt--;
        }
        it = temp;
        i++;
    }
    //qDebug() << "dead";
    return Head;
}
