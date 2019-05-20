#include<plan.h>

plan::plan(){
    gg = true;
}

plan::~plan(){
    delete PlanImage;
    delete PersonBackgroundSound;
}

void plan::init(int x, int y){
    Loc.plan.setX(x);
    Loc.plan.setY(y);
    Loc.plan.setWidth(PLANSIZE);
    Loc.plan.setHeight(PLANSIZE);
    PlanImage = new QPixmap;
    PlanImage->load(PicLocation);
}

void plan::destory(){
    gg = true;
}
