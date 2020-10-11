#ifndef POSITION_H
#define POSITION_H
#include <QtGlobal>
#include <QTime>

//![1]位置类用于生成地形图上的食物、障碍和工具
class position
{
public:
    position();
    struct point
    {
        int x,y;
        point(int a = 240,int b = 40)
        {
            x = a;
            y = b;
        }
    };

    point food[10];//食物数组
    point barrier[10];//障碍数组
    point tools[3];//工具
};
//![1]
#endif // POSITION_H
