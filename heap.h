//2252429蔡宇轩
#ifndef HEAP_H
#define HEAP_H
#include "node.h"
#include <QDebug>
#include <QTextDocument>
#include <QTextBlock>
#include <QTimeLine>
#include <QTimer>
#include <QGraphicsView>
#include <QPropertyAnimation>

class heap
{
public:
    heap(QWidget* mainwindow,QGraphicsScene* scene,QGraphicsView* view);
private:
    QVector<int>array;                          //后端数组
    node nodes[15];                             //前端结点

    bool readytoBuild;                          //标志是否可以开始建堆
    bool readytoSort;                           //标志是否可以开始排序

    QWidget* mainw;                             //主界面
    QGraphicsScene* scene;                      //scene
    QGraphicsView* view;                        //Graphicsview

    QTimer* time_interval;                      //延时
    QEventLoop* loop;                           //排序事件
    QEventLoop* pauseloop;                      //暂停事件

public:
    void setArrayValue(QVector<int>arr);        //设置数组的值
    int getArraySize();                         //获取当前array大小

    void AdjustHeap(int k,int n,bool toshow);   //调整大顶堆
    void HeapSort();                            //堆排序

    bool isreadytoBuild();                      //返回能否建堆
    bool isreadytoSort();                       //返回能否排序

    void renderNodes(int k);                    //前端渲染前k个二叉树结点
    void renderSwap(int swap1,int swap2);       //前端渲染下标分别为swap1和swap2的结点的交换过程
    void renderArray(int k);                    //前端渲染当前排序结果
    void AnimationPlay();                        //排序动画播放
    void AnimationPause();                       //排序动画暂停

    void swapNodeValue(int i,int j);            //将第i个node和第j个node的结点value互换
    QPointF getNodePos(int i);                  //获取二叉树上第i个结点的位置

private:
    void setTextAlign(QGraphicsTextItem* t);    //设置文本框居中显示

};

#endif // HEAP_H
