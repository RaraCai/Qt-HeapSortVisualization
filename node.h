//2252429蔡宇轩
#ifndef NODE_H
#define NODE_H
#include <QPointF>
#include <QColor>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsItem>

class node
{
public:
    //构造函数
    node();
private:
    int value;                              //当前结点的值
    QPointF pos;                            //当前结点在画布中的位置

    //状态常量
public:
    static int normal_radius;               //待排序未选中的结点半径
    //static int chosen_radius;             //待排序被选中的结点半径
    static QColor normal_color;             //待排序未选中结点颜色
    static QColor chosen_color;             //待排序被选中的结点颜色
    static QColor chosen_bg_color;          //已排序结点颜色
    static QColor txt_color;
    static QColor sorted_color;
    static int posx[15];                    //在画布上的x坐标
    static int posy[15];                    //在画布上的y坐标
public:
    void setValue(int val);                 //设置当前结点的值
    int getValue();                         //获取当前结点的值
    void setPos(int posx,int posy);         //设置结点位置
    QPointF getPos();                       //获取当前结点位置

};

#endif // NODE_H
