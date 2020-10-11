#ifndef GLUTTONOUSSNAKE_PLAYER_2_H
#define GLUTTONOUSSNAKE_PLAYER_2_H

#include"gluttonoussnakewindow_player_1.h"

//![1]贪吃蛇游戏的窗口类
class GluttonousSnakeWindow_player2: public snakewindow
{
    Q_OBJECT
public:
    GluttonousSnakeWindow_player2();

    snake player_1;//贪吃蛇类对象
    snake player_2;
    int score_1=0;//得分
    int score_2=0;
    class position set;

protected:
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *ev) override;
    void DGo();//前进
    void DEat(snake &p,int &score);//吃食物
    void StopGame();//停止游戏

private:
    QLCDNumber *score_LCD_1;
    QLabel *sc1;

private slots:
    void timeUpdate();
};
//![1]

#endif // GLUTTONOUSSNAKE_PLAYER_2_H
