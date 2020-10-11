#include "aisnakewindow.h"

AISnakeWindow::AISnakeWindow(){}

//! [1]渲染事件
void AISnakeWindow::paintEvent(QPaintEvent*p)
{
    void Go(snake &p,QTimer *t);//前进
    void AIEat(snake &p,position &s,QTimer *t);//AI判断前进方向
    void eat(snake &player,position &set,QTimer *t,int &score);//吃食物

    QPainter pen(this);

    score_LCD->display(score);

    //根据彩蛋的选择改变定时器间隔提高蛇移动的速度
    t->setInterval(speed);

    //绘制游戏背景图案
    pen.drawImage(QRect(200,0,600,600),QImage(":/new/prefix1/background1.jpg"));

    //绘制地形
    pen.drawImage(QRect(set.food[0].x,set.food[0].y,20,20),QImage(":/new/prefix1/apple.png"));

    //根据目前方向令蛇前进
    Go(player,t);

    //蛇吃食物事件
    eat(player,set,t,score);

    //AI蛇寻找食物事件
    AIEat(player,set,t);

    //判断蛇是否撞到尾巴或碰到墙壁死亡
    player.life();

    //画出蛇
    if(!player.isdead)
    {
        snake::bodynode *tmp=player.head;
        while(tmp!=nullptr)
        {
            pen.drawImage(QRect(tmp->x,tmp->y,20,20),QImage(":/new/prefix1/snakebody.png"));
            tmp=tmp->next;
        }
    }
    //蛇死亡的话画出结束界面
    else
    {
        pen.drawImage(QRect(200,0,600,600),QImage(":/new/prefix1/gameover.jpg"));
        this->close();
    }
}
//! [1]

//! [2]计时器开始时蛇前进事件
void Go(snake &p,QTimer *t)
{
    if(t->isActive()) p.goahead();
}
//! [2]

//! [3]蛇吃食物事件
void eat(snake &player,position &set,QTimer *t,int &score)
{
    if(t->isActive())
    {
        if(player.head->x == set.food[0].x&&player.head->y == set.food[0].y)
            player.iseat = 1;
        if(!player.iseat)
        {
            snake::bodynode *extra;
            extra=player.tail;
            player.tail=player.tail->prev;
            player.tail->next=nullptr;
            delete extra;
        }
        else{
            player.length++;
            score+=10;
            if(player.speed>=20) player.speed=300-player.length*10;
            else player.speed=10;

            //生成新的食物位置
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
            bool flag=0;
            do{
                snake::bodynode *comp=player.head;
                set.food[0].x = (qrand()%30)*20+200;
                set.food[0].y = (qrand()%30)*20;
                while(comp != nullptr)
                {
                    if(comp->x == set.food[0].x&&comp->y == set.food[0].y)
                    {
                        flag = 1;
                        break;
                    }
                    else flag = 0;
                    comp = comp->next;
                }
            }while(flag);
            player.iseat=0;
        }
    }
}
//! [3]

//! [4]自动寻找食物事件
void AIEat(snake &p,position &s,QTimer *t){
    if(t->isActive())
    {
        bool aiflag=1;
        bool isnodirection=0;
        bool isBody(snake &p,int d);
        int rd=0;
        if(isBody(p,0)&&isBody(p,1)&&isBody(p,2)&&isBody(p,3))
        {
            p.isdead=1;
            return;
        }
        while(aiflag)
        {
            if(aiflag&&((p.head->x<s.food[0].x)||(isnodirection==1&&rd==3)))
            {
                if((p.direction!=2)&&(!isBody(p,3)))
                {
                    p.direction=3;
                    aiflag=0;
                }
            }

            if(aiflag&&((p.head->x>s.food[0].x)||(isnodirection==1&&rd==2)))
            {
                if(p.direction!=3&&(!isBody(p,2)))
                {
                    p.direction=2;
                    aiflag=0;
                }
            }

            if(aiflag&&((p.head->x==s.food->x)||(isnodirection==1)))
            {
                if((s.food->y>p.head->y&&p.direction==0)||(s.food->y<p.head->y&&p.direction==1))
                {
                    qDebug()<<p.direction<<" ";
                    if(!isBody(p,3)) p.direction=3;
                    else if(!isBody(p,2)) p.direction=2;
                    aiflag=0;
                }
            }

            if(aiflag&&((p.head->y<s.food[0].y)||(isnodirection==1&&rd==1)))
            {
                if(p.direction!=0&&(!isBody(p,1)))
                {
                    p.direction=1;
                    aiflag=0;
                }
            }

            if(aiflag&&((p.head->y>s.food[0].y)||(isnodirection==1&&rd==0)))
            {
                if(p.direction!=1&&(!isBody(p,0)))
                {
                    p.direction=0;
                    aiflag=0;
                }
            }
            if(aiflag&&(p.head->y==s.food->y||(isnodirection==1)))
            {
                if((s.food->x>p.head->x&&p.direction==2)||(s.food->x<p.head->x&&p.direction==3))
                {
                    qDebug()<<p.direction<<" ";
                    if(!isBody(p,1))
                    {
                        p.direction=1;
                        aiflag=0;
                    }
                    if(!isBody(p,0))
                    {
                        p.direction=0;
                        aiflag=0;
                    }

                }
            }

            if(aiflag)
            {
                isnodirection=1;
                qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
                rd=qrand()%4;
            }
        }
    }
}
//! [4]

//! [5]判断前方是否有食物
bool isBody(snake &p,int d)
{
    bool iswall(int x,int y);
    snake::bodynode *tmp=p.head->next;
    bool isBody=0;

    if(d==0)
    {
        while(tmp!=nullptr)
        {
            if(((p.head->x==tmp->x)&&(((p.head->y)-20)==tmp->y))||iswall(p.head->x,((p.head->y)-20)))
            {
                isBody=1;
                break;
            }
            tmp=tmp->next;
        }
    }
    if(d==1)
    {
        while(tmp!=nullptr)
        {
            if(((p.head->x==tmp->x)&&(((p.head->y)+20)==tmp->y))||iswall(p.head->x,((p.head->y)+20)))
            {
                isBody=1;
                break;
            }
            tmp=tmp->next;
        }


    }
    if(d==2)
    {
        while(tmp!=nullptr)
        {
            if(((p.head->y==tmp->y)&&(((p.head->x)-20)==tmp->x))||iswall(((p.head->x)-20),p.head->y))
            {
                isBody=1;
                break;
            }
            tmp=tmp->next;
        }

    }
    if(d==3)
    {
        while(tmp!=nullptr)
        {
            if(((p.head->y==tmp->y)&&(((p.head->x)+20)==tmp->x))||iswall(((p.head->x)+20),p.head->y))
            {
                isBody=1;
                break;
            }
            tmp=tmp->next;
        }

    }
    return isBody;
}
//![5]

//![6]判断前面是否有墙
bool iswall(int x,int y)
{
    bool iswall=0;
    if(x<200||y<0||x>780||y>580)
    {
        iswall = 1;
    }
    return iswall;
}
//! [6]
