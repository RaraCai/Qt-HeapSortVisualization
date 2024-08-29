//2252429蔡宇轩
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QToolTip>
#include <QStyleOption>
#include "window_intro.h"
#include "myguistyle.h"
#include "heap.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *p);
    window_intro* profile;              //子页面profile
    myMsgbox* mybox;                    //自定义消息弹窗
    heap* Heap;                         //后端管理的堆结构
    QTimer* time_interval;              //管理延时
    QPixmap play_pm;                    //播放
    QPixmap pause_pm;                   //暂停

protected:
    void renderNodes(int k);            //前端绘制二叉树

private slots:
    void on_exitButton_clicked();
    void on_profileButton_clicked();
    void on_InputOKButton_clicked();
    void on_buildheapButton_clicked();
    void on_sortButton_clicked();
    void on_play_clicked();
    void on_pause_clicked();

protected:
    QGraphicsScene *scene;              //scene
    QString invalid_boxStyle="<html>"
                                 "<head>"
                                 "<style type=\"text/css\">"
                                 "p.first {font-size: 8pt; color: black; font-family: '微软雅黑', sans-serif;font-weight:semi-bold;}"
                                 "p.second { font-size: 10pt; color: black; font-family: '微软雅黑', sans-serif;font-weight:bold;} "
                                 "p.third { font-size: 8pt; color: grey; font-family: '微软雅黑', sans-serif;font-weight:semi-bold;}"
                                 "</style>"
                                 "</head>"
                                 "<body>"
                                 "<p class=\"first\">错误！</p>"
                                 "<p class=\"second\">输入内容非法，请按正确格式重新输入</p>"
                                 "<p class=\"third\">Invalid input, try again</p>"
                                 "</body>"
                                 "</html>";
    QString overflow_boxStyle="<html>"
                               "<head>"
                               "<style type=\"text/css\">"
                               "p.first {font-size: 8pt; color: black; font-family: '微软雅黑', sans-serif;font-weight:semi-bold;}"
                               "p.second { font-size: 10pt; color: black; font-family: '微软雅黑', sans-serif;font-weight:bold;} "
                               "p.third { font-size: 8pt; color: grey; font-family: '微软雅黑', sans-serif;font-weight:semi-bold;}"
                               "</style>"
                               "</head>"
                               "<body>"
                               "<p class=\"first\">诶呀！</p>"
                               "<p class=\"second\">输入数字太多啦，最多输入15个哦</p>"
                               "<p class=\"third\">Too many numbers, try again</p>"
                               "</body>"
                               "</html>";
    QString noBuild_boxStyle="<html>"
                                "<head>"
                                "<style type=\"text/css\">"
                                "p.first {font-size: 8pt; color: black; font-family: '微软雅黑', sans-serif;font-weight:semi-bold;}"
                                "p.second { font-size: 10pt; color: black; font-family: '微软雅黑', sans-serif;font-weight:bold;} "
                                "p.third { font-size: 8pt; color: grey; font-family: '微软雅黑', sans-serif;font-weight:semi-bold;}"
                                "</style>"
                                "</head>"
                                "<body>"
                                "<p class=\"first\">错误！</p>"
                                "<p class=\"second\">缺少合法数据以构建堆结构</p>"
                                "<p class=\"third\">Lack of data, try again</p>"
                                "</body>"
                                "</html>";
    QString okBuild_boxStyle="<html>"
                               "<head>"
                               "<style type=\"text/css\">"
                               "p.first {font-size: 8pt; color: black; font-family: '微软雅黑', sans-serif;font-weight:semi-bold;}"
                               "p.second { font-size: 10pt; color: black; font-family: '微软雅黑', sans-serif;font-weight:bold;} "
                               "p.third { font-size: 8pt; color: grey; font-family: '微软雅黑', sans-serif;font-weight:semi-bold;}"
                               "</style>"
                               "</head>"
                               "<body>"
                               "<p class=\"first\">提示</p>"
                               "<p class=\"second\">成功录入数据，点击[建堆]查看堆结构</p>"
                               "<p class=\"third\">Succeed,check your heap now</p>"
                               "</body>"
                               "</html>";
    QString over_boxStyle="<html>"
                               "<head>"
                               "<style type=\"text/css\">"
                               "p.first {font-size: 8pt; color: black; font-family: '微软雅黑', sans-serif;font-weight:semi-bold;}"
                               "p.second { font-size: 10pt; color: black; font-family: '微软雅黑', sans-serif;font-weight:bold;} "
                               "p.third { font-size: 8pt; color: grey; font-family: '微软雅黑', sans-serif;font-weight:semi-bold;}"
                               "</style>"
                               "</head>"
                               "<body>"
                               "<p class=\"first\">提示</p>"
                               "<p class=\"second\">排序完成，点击[OK]清空屏幕</p>"
                               "<p class=\"third\">Succeed,clean the screen</p>"
                               "</body>"
                               "</html>";


};
#endif // MAINWINDOW_H
