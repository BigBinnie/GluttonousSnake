#include"snake.h"

//! [1]蛇类的构造函数-生成一个双向链表
snake::snake()
{
    head = new bodynode(200,20,nullptr,nullptr);
    tail = new bodynode(200,0,nullptr,head);
    head->next = tail;
}
//! [1]

//! [2]根据蛇是否吃到食物选择不同的前进方式
void snake::goahead()
{
    bodynode *newbody;
    newbody=new bodynode(0,0,head,nullptr);

    if( direction == 0)
    {
        newbody->y = head->y - 20;
        newbody->x = head->x;
    }
    if( direction == 1)
    {
        newbody->y = head->y + 20;
        newbody->x = head->x;
    }
    if( direction == 2)
    {
        newbody->x = head->x - 20;
        newbody->y = head->y;
    }
    if( direction == 3)
    {
        newbody->x = head->x + 20;
        newbody->y = head->y;
    }

    head->prev = newbody;
    head = newbody;
}
//! [2]

//! [3]判断蛇是否撞到自己或者墙壁而死亡
void snake::life()
{
    bodynode *exa=head->next;

    while((exa!=nullptr)&&(length!=1))
    {
        if(exa->x==head->x&&exa->y==head->y)
        {
            isdead=1;
            break;
        }
        exa = exa->next;
    }

    if(head->x<200||head->y<0||head->x>780||head->y>580)
    {
        isdead = 1;
    }
}
//! [3]
