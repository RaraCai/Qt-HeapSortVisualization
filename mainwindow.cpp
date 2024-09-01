//2252429蔡宇轩
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //隐藏标题栏
    setWindowFlags(Qt::FramelessWindowHint);//无边框置顶
    this->setStyleSheet("#Widget{background-color: rgb(255,255,255);}");

    //初始化各成员
    this->profile=new window_intro(this);
    profile->show();

    this->scene=new QGraphicsScene;
    this->scene->setSceneRect(325,-140,920,660);
    this->mybox=new myMsgbox;
    this->Heap= new heap(this,this->scene,ui->graphicsView);

    this->play_pm=QPixmap(":/icon/icon/icon_play_pressed.png");
    this->play_pm.scaled(ui->statusicon->size(), Qt::KeepAspectRatio);
    this->pause_pm=QPixmap(":/icon/icon/icon_pause_pressed.png");
    this->pause_pm.scaled(ui->statusicon->size(), Qt::KeepAspectRatio);

    // 设置QToolTip样式
    QToolTip::setFont(QFont("华文中宋",8));

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setScene(this->scene);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete profile;
    delete scene;
    delete mybox;
    delete Heap;
}

void MainWindow::paintEvent(QPaintEvent *p){
    //绘制圆角样式
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p1(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p1, this);//绘制样式

    QBitmap bmp(this->size());
    bmp.fill();
    QPainter painter(&bmp);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawRoundedRect(bmp.rect(), 20, 20);
    setMask(bmp);
}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}

void MainWindow::on_profileButton_clicked()
{
    this->profile->show();
}

void MainWindow::on_InputOKButton_clicked()
{
    //若当前循环事件正在运行，按键无效
    if(this->Heap->isLoopRunning())
        return;

    //检查输入内容是否合法：只包含数字和空格
    QString input_str=ui->input->toPlainText().trimmed();
    bool valid=true;
    if(input_str.isEmpty()){
        this->mybox->showMymsgbox(noBuild_boxStyle);
        return;
    }

    for(auto&c:input_str){
        if(!c.isDigit() && !c.isSpace())
            valid=false;
    }

    if(valid){
        if(input_str.split(' ').size()>15){//输入数字过多
            this->mybox->showMymsgbox(overflow_boxStyle);
            ui->input->clear();
        }
        else{//正确且数量合理            
            //存入新的数据
            QVector<int>arr;
            for(auto&s:input_str.split(' ')){
                arr.push_back(s.toInt());
            }
            //将该数组传给Heap
            this->Heap->setArrayValue(arr);
            //提示创建成功
            this->mybox->showMymsgbox(okBuild_boxStyle);
        }
    }
    else{//输入非法，不执行操作
        this->mybox->showMymsgbox(invalid_boxStyle);
        ui->input->clear();
    }
}

void MainWindow::on_buildheapButton_clicked()
{
    //若当前循环事件正在运行，按键无效
    if(this->Heap->isLoopRunning())
        return;

    if(Heap->isreadytoBuild()){
        this->Heap->renderNodes(this->Heap->getArraySize());
        this->Heap->renderArray(this->Heap->getArraySize());
    }
    else{
        this->mybox->showMymsgbox(noBuild_boxStyle);
        ui->input->clear();
    }
}

void MainWindow::on_sortButton_clicked()
{
    //若当前循环事件正在运行，按键无效
    if(this->Heap->isLoopRunning())
        return;

    if(Heap->isreadytoBuild() && Heap->isreadytoSort()){
        Heap->HeapSort();
        //提示排序结束
        this->mybox->showMymsgbox(over_boxStyle);
        //清空
        this->scene->clear();
        ui->input->clear();

    }
    else{
        this->mybox->showMymsgbox(noBuild_boxStyle);
        ui->input->clear();
    }
}

void MainWindow::on_play_clicked()
{
    //不在pauseloop说明动画正常执行中，不用其他操作
    if(!this->Heap->isPauseLoopRunning())
        return;

    if(this->Heap->isreadytoBuild() && this->Heap->isreadytoSort()){
        QLabel* icon=ui->statusicon;
        icon->setPixmap(QPixmap());
        icon->setScaledContents(true);
        icon->setPixmap(this->play_pm);
        QTimer* timer=new QTimer(this);
        timer->setSingleShot(true);
        timer->setInterval(800);
        connect(timer,&QTimer::timeout,[=]{
            icon->setPixmap(QPixmap());
        });
        timer->start();
        //play
        this->Heap->AnimationPlay();
    }
}

void MainWindow::on_pause_clicked()
{
    //在pauseloop说明动画已经被暂停，不用其他操作
    if(this->Heap->isPauseLoopRunning())
        return;

    if(this->Heap->isreadytoBuild() && this->Heap->isreadytoSort()){
        QLabel* icon=ui->statusicon;
        icon->setScaledContents(true);
        icon->setPixmap(this->pause_pm);
        //pause
        this->Heap->AnimationPause();
    }
}

