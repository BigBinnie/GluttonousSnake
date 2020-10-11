#ifndef AISNAKEWINDOW_H
#define AISNAKEWINDOW_H

#include"gluttonoussnakewindow_player_2.h"

//![1]AI蛇对象
class AISnakeWindow:public snakewindow
{
public:
    AISnakeWindow();

    snake player;//贪吃蛇类对象
    class position set;//地形类对象
    int score=0;//得分

protected:
    void paintEvent(QPaintEvent *) override;
};
//![1]
#endif // AISNAKEWINDOW_H
