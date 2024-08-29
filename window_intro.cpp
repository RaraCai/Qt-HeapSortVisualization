//2252429蔡宇轩
#include "window_intro.h"
#include "ui_window_intro.h"

window_intro::window_intro(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::window_intro)
{
    ui->setupUi(this);

    //设置profile的初始状态
    resize(400,760);
    //动画
    animation = new QPropertyAnimation(this,"geometry");
    animation->setEasingCurve(QEasingCurve::InOutQuint);
    animation->setDuration(1000);
}

window_intro::~window_intro()
{
    delete ui;
    delete animation;
}
void window_intro::show(){

    animation->setStartValue(QRect(-400,0,400,760));
    animation->setEndValue(QRect(0,0,400,760));
    animation->start();
}

void window_intro::hide(){
    animation->setStartValue(QRect(0,0,400,760));
    animation->setEndValue(QRect(-400,0,400,760));
    animation->start();
}

void window_intro::on_backButton_clicked()
{
    this->hide();
}

