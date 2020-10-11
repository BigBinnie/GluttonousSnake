#ifndef SNAKE_H
#define RASTERWINDOW_H

//![1]蛇类
class snake
{
public:
    struct bodynode
    {
        int x;
        int y;
        bodynode *next,*prev;

        bodynode( int a = 0, int b = 0, bodynode *n =nullptr, bodynode*p = nullptr)
        {   x = a;
            y = b;
            next = n;
            prev = p;
        }
        bodynode():next(nullptr),prev(nullptr){}
        ~bodynode(){}
    };

    bool isdead = 0;
    bool iseat = 0;
    bool isable = 0;
    bool ispink=0;
    int speed = 300;
    int length = 2;
    int direction = 1;

    bodynode *head, *tail;
    snake();
    void goahead();//前进
    void life();//判断是否死亡
};
//![1]
#endif // SNAKE_H
