#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include <QApplication>
#include <QtGui>
#include<QPainter>
#include<QPaintEvent>
#include<QLCDNumber>
#include<QLabel>
#include<QPushButton>
#include<QMessageBox>
#include "mainwindow.h"
#include"snake.h"
#include"position.h"

//![1]不同模式下游戏窗口的基类，控制按钮和定时器
class snakewindow: public RasterWindow
{
    Q_OBJECT
public:
    snakewindow();

    QPushButton *btn_begin=new QPushButton;
    QPushButton *btn_pause=new QPushButton;
    QPushButton *btn_stop=new QPushButton;
    QTimer *t;
    QLCDNumber *score_LCD;
    QLabel *sc;
    QMessageBox *m;
    int speed=200;

public slots:
    void on_btn_begin_cliked();
    void on_btn_pause_cliked();
    void on_btn_stop_cliked();
};
//![1]
#endif // SNAKEWINDOW_H
