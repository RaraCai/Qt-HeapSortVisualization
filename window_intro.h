//2252429蔡宇轩
#ifndef WINDOW_INTRO_H
#define WINDOW_INTRO_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class window_intro;
}

class window_intro : public QWidget
{
    Q_OBJECT

public:
    explicit window_intro(QWidget *parent = nullptr);
    ~window_intro();

private:
    Ui::window_intro *ui;
    QPropertyAnimation *animation=nullptr;
public:
    void show();                        //显示界面
    void hide();                        //隐藏界面
private slots:
    void on_backButton_clicked();
};

#endif // WINDOW_INTRO_H
