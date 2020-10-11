#ifndef GLUTTONOUSSNAKE_PLAYER_1_H
#define GLUTTONOUSSNAKE_PLAYER_1_H


#include"snakewindow.h"

//! [1]贪吃蛇游戏的窗口类
class GluttonousSnakeWindow_player1: public snakewindow
{
Q_OBJECT
public:
    GluttonousSnakeWindow_player1();
    ~GluttonousSnakeWindow_player1() override;

    snake player;//贪吃蛇类对象
    class position set;//地形类对象
    int score=0;//得分

    //显示道具作用的文本框
    QLabel *speed;
    QLabel *wall;
    QLabel *doublescore;

protected:
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *ev) override;
    void stopGame();//停止游戏
    void GO();//前进
    void Eat();//吃食物
    void produce(int i);//产生新的道具

public slots:
    void on_btn_begin_cliked();
    void on_btn_stop_cliked();
    void timerupdate();

};
//! [1]
#endif // GLUTTONOUSSNAKE_PLAYER_1_H
