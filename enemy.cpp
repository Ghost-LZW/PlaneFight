#include<enemy.h>

enemy::enemy(){
    gg = true;
    my.Speed = 10;
    my.Attac = 10;
    my.level = 1;
    vx = 10;
    vy = 0;
    PlanImage = new QPixmap;
    PlanImage->load(PicLocation);
    cnt = 0;
}

enemy::~enemy(){
    delete head;
    delete Phead;
    delete PlanImage;
}

bool enemy::check(int herosize, int basex, int basey){
    Plan *it = Phead;
    while(it != nullptr){
        if(it->plan.x() < basex + herosize && it->plan.x() > basex && ((it->plan.y() > basey && it->plan.y() < basey + herosize) || (it->plan.y() + PLANSIZE > basey && it->plan.y() + PLANSIZE < basey + herosize)))
            return  false;
        it = it->next;
    }
    return  true;
}

void enemy::add(int x, int y, int blood){
    Plan *it;
    it = new Plan;
    it->Blood = blood;
    it->plan.setX(x);
    it->plan.setY(y);
    it->plan.setWidth(PLANSIZE);
    it->plan.setHeight(PLANSIZE);
    it->next = nullptr;
    if(Phead == nullptr)
        Phead = it;
    else {
        it->next = Phead;
        Phead = it;
    }
    cnt++;
}

int enemy::getinf(int i, int wh){
    Plan *it = Phead;
    for (int j = 0; j < i && it != nullptr; ++j)
        it = it->next;
    if (it == nullptr)
        return -1;
    else
        return (wh == 0) ? int(it->plan.x()) : int(it->plan.y());
}

void enemy::destory(int k){
    Plan *it = Phead;
    if(k == 0){
        Phead = Phead->next;
        delete it;
    }
    else{
    for(int i = 0; i < k - 1; i++)
        it = it->next;
    Plan *temp = it->next;
    it->next = temp->next;
    delete temp;
    }
    --cnt;
}

void enemy::move(){
    Plan *it = Phead;
    int i = 0;
    while(it != nullptr){
        it->plan.setX(it->plan.x() - vx);
        it->plan.setY(it->plan.y() - vy);
        it->plan.setWidth(PLANSIZE);
        it->plan.setHeight(PLANSIZE);
        Plan *temp = it->next;
        if(it->plan.x() < 0 || it->plan.y() < 0){
            destory(i);
            cnt--;
            i--;
        }
        i++;
        it = temp;
    }
}
