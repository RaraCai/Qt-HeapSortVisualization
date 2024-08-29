//2252429蔡宇轩
#ifndef MYGUISTYLE_H
#define MYGUISTYLE_H
#include <QString>
#include <QMessageBox>
#include <QPushButton>
#include <QColorDialog>
#include <QComboBox>
#include <QListWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QTimer>


//封装无标题框的消息弹窗
class myMsgbox{
protected:
    //紫色OK-button样式
    const QString ok_buttonStyle="QPushButton{"
                                   "background-color:white;"
                                   "color:#603BE6;"
                                   "font-weight:bold;"
                                   "border-radius:12px;"
                                   "width:60px;"
                                   "height:25px;"
                                   "border:1px solid #603BE6;"
                                   "}"
                                   "QPushButton:pressed{"
                                   "background-color:#41289c;"
                                   "color:#cccccc;"
                                   "}"
                                   "QPushButton:hover{"
                                   "background-color:#603BE6;"
                                   "color:white;"
                                   "}";

    //ColorDialog样式
    QString colordlg_style="QPushButton{"
                             "background-color:white;"
                             "color:grey;"
                             "border-radius:6px;"
                             "border:1px solid #cccccc;"
                             "font-size:8pt;"
                             "height:25px;"
                             "padding-left:10px;"
                             "padding-right:10px;"
                             "}"
                             "QPushButton:hover{"
                             "border:1px solid #ffcc33;"
                             "color:#ffcc33;"
                             "}"
                             "QPushButton:pressed{"
                             "border:none;"
                             "background-color:#E6B82E;"
                             "color:white;"
                             "}"
                             "QColorDialog{"
                             "background-color:white;"
                             "border:1px groove #cccccc;"
                             "border-radius:15px;"
                             "color:#603BE6;"
                             "}"
                             "QLineEdit{"
                             "background-color:white;"
                             "border-radius:6px;"
                             "border:1px solid #cccccc;"
                             "padding-left:3px;padding-right:3px;"
                             "}"
                             "QSpinBox{"
                             "width:60px;"
                             "height:30px;"
                             "border:1px solid #cccccc;"
                             "border-radius:6px;"
                             "}"
                             "QSpinBox:focus{"
                             "border:1px solid #ffcc33;"
                             "}"
                             "QSpinBox::up-button{width:20px;}"
                             "QSpinBox::down-button{width:20px;}"
        ;

public:
    myMsgbox(){}
    ~myMsgbox(){};
    //生成自定义样式的无标题框消息弹窗
    void showMymsgbox(QString text){
        QMessageBox* mybox=new QMessageBox;
        mybox->setStyleSheet("QMessageBox{"
                             "background-color:white;"
                             "border-radius:10px;"
                             "border:1px solid #cccccc;"
                             "}");
        mybox->setWindowTitle("");
        mybox->setWindowFlags(mybox->windowFlags() & ~Qt::WindowType_Mask);
        mybox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
        mybox->setTextFormat(Qt::RichText);
        mybox->setText(text);

        //添加确定按钮
        QPushButton* okbutton = new QPushButton("OK");
        okbutton->setStyleSheet(ok_buttonStyle);
        mybox->addButton(okbutton,QMessageBox::AcceptRole);
        //显示
        mybox->exec();
    }
    //生成自定义样式的颜色选择框并返回选中的颜色
    QColor showMycolorDialog(){
        QColorDialog* mycolordlg=new QColorDialog;
        //隐藏标题框
        mycolordlg->setWindowTitle("地铁线路颜色选择");
        mycolordlg->setWindowFlags(mycolordlg->windowFlags() & ~Qt::WindowType_Mask);
        mycolordlg->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
        //设置样式
        mycolordlg->setStyleSheet(colordlg_style);
        //显示
        mycolordlg->exec();
        //返回结果
        return mycolordlg->selectedColor();
    }
    //生成自定义样式的bubbleTips
    void showMybubble(QString text){
        //新的widget并隐藏标题框
        QMessageBox* bubble=new QMessageBox;
        bubble->setStandardButtons(QMessageBox::NoButton); // 移除所有标准按钮
        bubble->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
        //设置文字和格式
        bubble->setStyleSheet("QMessageBox{"
                              "background-color:white;"
                              "border:1px solid #603be6;"
                              "border-radius:10px;"
                              "height:200px;"
                              "}");
        bubble->setText(text);

        //移动位置
        bubble->move(850,420);
        QTimer::singleShot(1200, bubble, SLOT(accept()));
        bubble->exec();
    }
};
//前端CSS-HTML样式----------------------------------------------


#endif // MYGUISTYLE_H
