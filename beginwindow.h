#ifndef BEGINWINDOW_H
#define BEGINWINDOW_H

#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include<QPainter>
#include<QPaintEvent>
#include<QPushButton>
#include<QLabel>
#include"aisnakewindow.h"
#include<QPixmap>
#include<Qsize>

//![1]开始界面类
class BeginWindow:public RasterWindow
{
public:
    BeginWindow();
protected:
    void paintEvent(QPaintEvent *) override;

private:
    QPushButton *btn1=new QPushButton;
    QPushButton *btn2=new QPushButton;
    QPushButton *btn3=new QPushButton;
    QTimer *t;
    QLabel *s;
    GluttonousSnakeWindow_player1 *p1;
    GluttonousSnakeWindow_player2 *p2;
    AISnakeWindow *p3;

public slots:
    void on_btn1_cliked();
    void on_btn2_cliked();
    void on_btn3_cliked();

};
//![1]
#endif // BEGINWINDOW_H
