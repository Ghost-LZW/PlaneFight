#include<normalbullet.h>
#include<QSound>

normalbullet::normalbullet(){
    BulletPic = new QPixmap;
    BulletPic->load(PicLocation);
    BulletSound = new QSound(SounLocation);
    BulletSIZE = 10;
    head = nullptr;
    cnt = 0;
    xspeed = 20;
    yspeed = 1;
}

normalbullet::~normalbullet(){
    delete BulletPic;
    delete BulletSound;
}

void normalbullet::add(int x, int y, int harm, int fx){
     Bullet *it;
     it = new Bullet;
     it->fx = fx;
     it->harm = harm;
     it->bull.setX(x);
     it->bull.setY(y);
     it->bull.setWidth(BulletSIZE);
     it->bull.setHeight(BulletSIZE);
     it->next = nullptr;
     if(head == nullptr){
         head = it;
     }
     else {
         it->next = head;
         head = it;
     }
     cnt++;
}

bool normalbullet::check(int herosize, int basex, int basey, int flag){
     Bullet *it = head;
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
     return  true;
}

/*bool bullet::check(int x, int y, int flag)  // dead=0
{
    Bair *p = head;
    while (p != NULL)
    {
        Bair *nxt = p->next;
        if (p->flag | flag)
        {
            if (flag == 0 && (p->rect.x() >= x && p->rect.x() <= x + SizeEnemy) && (p->rect.y() >= y && p->rect.y() <= y + SizeEnemy))
            {
                head = bullet::del(p);
                return 0;
            }
            else if (flag == 1 && (p->rect.x() > x && p->rect.x() < x + SizeHero) && (p->rect.y() > y && p->rect.y() < y + SizeHero))
            {
                head = bullet::del(p);
                return 0;
            }
        }
        p = nxt;
    }
    return 1;
}*/

void normalbullet::destory(int k){
    Bullet *it = head;
    if(k == 0){
        head = head->next;
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
}

void normalbullet::move(){
    Bullet *it = head;
    int i = 0;
    while (it != nullptr) {
        it->bull.setX(it->bull.x() + (it->fx ? xspeed : -xspeed));
        it->bull.setY(it->bull.y() + (it->fx ? yspeed : -yspeed));
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
}
