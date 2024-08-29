//2252429蔡宇轩
#include "node.h"

int node::normal_radius=20;
QColor node::normal_color=QColor("#CCCCCC");
QColor node::chosen_color=QColor("#603BE6");
QColor node::chosen_bg_color=QColor("#F2EBFF");
QColor node::txt_color=QColor("#787878");
QColor node::sorted_color=QColor("#FFE489");

//15个结点在画布上的位置
int node::posx[15]={795,555,1035,435,675,915,1155,375,495,615,735,855,975,1095,1215};
int node::posy[15]={30,160,160,290,290,290,290,420,420,420,420,420,420,420,420};

node::node(){}

void node::setValue(int val){
    this->value=val;
}
int node::getValue(){
    return this->value;
}
void node::setPos(int x,int y){
    this->pos.setX(x);
    this->pos.setY(y);
}
QPointF node::getPos(){
    return this->pos;
}

