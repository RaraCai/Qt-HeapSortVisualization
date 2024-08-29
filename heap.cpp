//2252429蔡宇轩
#include "heap.h"

heap::heap(QWidget* mainwindow,QGraphicsScene* scene,QGraphicsView* view) {
    this->mainw=mainwindow;
    this->scene=scene;
    this->view=view;
    this->time_interval=new QTimer(mainwindow);
    time_interval->setInterval(1000);
    this->loop=new QEventLoop;
    this->pauseloop=new QEventLoop;
    QObject::connect(time_interval, &QTimer::timeout, [&]() {
        loop->quit(); // 定时器超时退出事件循环
    });

    //设置状态
    this->readytoBuild=false;
    this->readytoSort=false;
}

void heap::setArrayValue(QVector<int>arr){
    this->array.clear();
    for(auto&i:arr){
        this->array.push_back(i);
    }
    //直接建立大顶堆
    int n=this->array.size();
    for(int i=(n-1/2);i>=0;i--){
        this->AdjustHeap(i,n,false);
    }
    //可以开始在前端render大顶堆
    this->readytoBuild=true;
    this->readytoSort=true;
    //给nodes和txtitem赋值
    for(int i=0;i<15;i++){
        this->nodes[i].setPos(node::posx[i],node::posy[i]);

        if(i<this->array.size()){
            this->nodes[i].setValue(this->array[i]);
        }
        else{//剩余的暂时赋值为0
            this->nodes[i].setValue(0);
        }
    }
}

void heap::AdjustHeap(int k,int n,bool toshow){
    int i=k;
    int j=2*i+1;//j是i(i是第k层)的孩子
    while(j<n){
        // 在数组边界内, 比较左右孩子，较大的孩子与根节点比较
        if(j<n-1 && this->array[j]<this->array[j+1])
            ++j;
        //渲染i和j的比较

        if(this->array[i]>this->array[j])
            break;
        else{
            //交换
            if(toshow)
                this->renderSwap(i,j);
            qSwap(this->array[i],this->array[j]);
            this->swapNodeValue(i,j);
            if(toshow){
                time_interval->start();
                loop->exec();
                this->renderNodes(n);
                this->renderArray(n);
            }
            i=j;j=2*i+1;
        }
    }
}

void heap::HeapSort(){

    int n=this->array.size();

    //开始sort之前，调整好的堆顶就是排序的第一个元素
    for(int i=1;i<n;i++){

        this->renderSwap(0,n-i);
        qSwap(this->array[0],this->array[n-i]);
        this->swapNodeValue(0,n-i);

        time_interval->start();
        loop->exec();
        this->renderNodes(n-i);
        this->renderArray(n-i);
        //重新调整为大顶堆
        this->AdjustHeap(0,n-i,true);

    }
    this->renderArray(0);

    this->readytoBuild=false;
    this->readytoSort=false;

}

bool heap::isreadytoBuild(){
    return this->readytoBuild;
}

bool heap::isreadytoSort(){
    return this->readytoSort;
}

void heap::renderNodes(int k){
    scene->clear();
    //先画连线
    for(int i=0;i<k;i++){
        //孩子结点和父结点相连
        QPointF parentpos,childpos;
        if(i){
            childpos=this->nodes[i].getPos();
            parentpos=this->nodes[(i-1)/2].getPos();
            QGraphicsLineItem* lineitem=new QGraphicsLineItem;
            lineitem->setPen(QPen(QColor(node::normal_color),3));
            lineitem->setPos(parentpos);
            lineitem->setLine(0,0,childpos.x()-parentpos.x(),childpos.y()-parentpos.y());

            scene->addItem(lineitem);
        }
    }

    //再画结点
    for(int i=0;i<k;++i){
        //结点圆圈
        QGraphicsEllipseItem* nodeitem=new QGraphicsEllipseItem;
        nodeitem->setRect(-node::normal_radius,-node::normal_radius,2*node::normal_radius,2*node::normal_radius);
        nodeitem->setPos(this->nodes[i].getPos());
        nodeitem->setPen(QPen(QColor(node::normal_color),3));//外围边框
        nodeitem->setBrush(QColor("white"));//内部实心圆圈

        scene->addItem(nodeitem);

        //结点文字
        QGraphicsTextItem* t=new QGraphicsTextItem;
        t->setFont(QFont("Arial Black",9,false));
        t->setPos(this->nodes[i].getPos().x()-node::normal_radius,this->nodes[i].getPos().y()-13);
        t->setPlainText(QString::number(this->nodes[i].getValue()));
        t->setDefaultTextColor(node::txt_color);
        t->setTextWidth(2*node::normal_radius);
        setTextAlign(t);

        scene->addItem(t);
    }

    this->view->setRenderHint(QPainter::Antialiasing);
    this->view->setScene(this->scene);
}

int heap::getArraySize(){
    return this->array.size();
}

void heap::swapNodeValue(int i,int j){
    int tmp=this->nodes[i].getValue();
    this->nodes[i].setValue(this->nodes[j].getValue());
    this->nodes[j].setValue(tmp);
}

QPointF heap::getNodePos(int i){
    return this->nodes[i].getPos();
}

void heap::renderSwap(int swap1,int swap2){

    QGraphicsEllipseItem* s1=new QGraphicsEllipseItem;
    QGraphicsEllipseItem* s2=new QGraphicsEllipseItem;
    s1->setRect(-node::normal_radius,-node::normal_radius,2*node::normal_radius,2*node::normal_radius);
    s2->setRect(-node::normal_radius,-node::normal_radius,2*node::normal_radius,2*node::normal_radius);
    s1->setPos(this->nodes[swap1].getPos());
    s2->setPos(this->nodes[swap2].getPos());
    s1->setPen(QPen(QColor(node::chosen_color),3));//外围边框
    s2->setPen(QPen(QColor(node::chosen_color),3));//外围边框
    s1->setBrush(QBrush(QColor(node::chosen_bg_color)));
    s2->setBrush(QBrush(QColor(node::chosen_bg_color)));

    QGraphicsTextItem* t1=new QGraphicsTextItem;
    t1->setFont(QFont("Arial Black",9,false));
    t1->setPos(this->nodes[swap1].getPos().x()-node::normal_radius,this->nodes[swap1].getPos().y()-13);
    t1->setPlainText(QString::number(this->nodes[swap1].getValue()));
    t1->setDefaultTextColor(node::chosen_color);
    t1->setTextWidth(2*node::normal_radius+1);
    setTextAlign(t1);

    QGraphicsTextItem* t2=new QGraphicsTextItem;
    t2->setFont(QFont("Arial Black",9,false));
    t2->setPos(this->nodes[swap2].getPos().x()-node::normal_radius,this->nodes[swap2].getPos().y()-13);
    t2->setPlainText(QString::number(this->nodes[swap2].getValue()));
    t2->setDefaultTextColor(node::chosen_color);
    t2->setTextWidth(2*node::normal_radius);
    setTextAlign(t2);

    scene->addItem(s1);
    scene->addItem(s2);

    scene->addItem(t1);
    scene->addItem(t2);

    //交换动画
    QPointF pos1=QPointF(nodes[swap1].getPos().x()-node::normal_radius,nodes[swap1].getPos().y()-13);
    QPointF pos2=QPointF(nodes[swap2].getPos().x()-node::normal_radius,nodes[swap2].getPos().y()-13);


    QPropertyAnimation* a1=new QPropertyAnimation(t1,"pos");
    a1->setEasingCurve(QEasingCurve::InOutBounce);
    a1->setDuration(400);
    a1->setStartValue(pos1);
    a1->setEndValue(pos2);

    QPropertyAnimation* a2=new QPropertyAnimation(t2,"pos");
    a2->setEasingCurve(QEasingCurve::InOutBounce);
    a2->setDuration(400);
    a2->setStartValue(pos2);
    a2->setEndValue(pos1);

    a1->start();
    a2->start();
}

void heap::renderArray(int k){
    for(int i=0;i<15;++i){
        //矩形框
        QGraphicsRectItem* rectitem=new QGraphicsRectItem;
        rectitem->setRect(-30,-20,60,40);
        rectitem->setPos(QPointF(370+i*60,-50));
        rectitem->setPen(QColor("#ABABAB"));
        if(i>=this->array.size()){//未使用
            rectitem->setBrush(QBrush(QColor("#f5f5f5")));
            this->scene->addItem(rectitem);
        }
        else{
            //文字
            QGraphicsTextItem* t=new QGraphicsTextItem;
            t->setFont(QFont("Arial Black",13,false));
            t->setPos(QPointF(340+i*60,-65));
            t->setPlainText(QString::number(this->nodes[i].getValue()));
            t->setTextWidth(60);
            setTextAlign(t);

            if(i>=k){//已排序好
                rectitem->setBrush(QBrush(node::sorted_color));
                t->setDefaultTextColor(QColor("#ABABAB"));
            }
            else
                t->setDefaultTextColor(QColor("black"));

            this->scene->addItem(rectitem);
            this->scene->addItem(t);

        }
    }
}

void heap::setTextAlign(QGraphicsTextItem* t){
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignCenter);
    QTextCursor cursor = t->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(format);
    cursor.clearSelection();
    t->setTextCursor(cursor);
}

void heap::AnimationPlay(){
    if(this->pauseloop->isRunning()){
        this->pauseloop->quit();
    }
}

void heap::AnimationPause(){
    if(!this->pauseloop->isRunning()){
        this->pauseloop->exec();
    }
}
