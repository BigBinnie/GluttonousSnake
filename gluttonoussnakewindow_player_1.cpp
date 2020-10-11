#include "gluttonoussnakewindow_player_1.h"

//! [1]贪吃蛇窗口类的构造函数
GluttonousSnakeWindow_player1::GluttonousSnakeWindow_player1()
{
    //在游戏窗口左侧显示道具功能
    speed=new QLabel(this);
    wall=new QLabel(this);
    doublescore=new QLabel(this);

    speed->setText("Speed Down");
    speed->setGeometry(QRect(80,270,80,20));
    speed->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    speed->setStyleSheet("background-color: #B2DFEE;font-size:11px;color:black");

    wall->setText("Through Walls");
    wall->setGeometry(QRect(80,300,80,20));
    wall->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    wall->setStyleSheet("background-color: #B2DFEE;font-size:11px;color:black");

    doublescore->setText("Double Score");
    doublescore->setGeometry(QRect(80,330,80,20));
    doublescore->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    doublescore->setStyleSheet("background-color: #B2DFEE;font-size:11px;color:black");

    //定时器
    t=new QTimer(this);
    connect(t,SIGNAL(timeout()),this,SLOT(timerupdate()));
}
//! [1]

//! [2]键盘敲击事件
void GluttonousSnakeWindow_player1::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Up)
    {
        if(player.direction!=1)
            player.direction = 0;
    }
    if(ev->key() == Qt::Key_Down)
    {
        if(player.direction!=0)
            player.direction = 1;
    }
    if(ev->key() == Qt::Key_Left)
    {
        if(player.direction!=3)
            player.direction = 2;
    }
    if(ev->key() == Qt::Key_Right)
    {
        if(player.direction!=2)
            player.direction = 3;
    }

}
//! [2]

//! [3]渲染事件
void GluttonousSnakeWindow_player1::paintEvent(QPaintEvent*p)
{  
    QPainter pen(this);

    //绘制游戏背景图案
    pen.drawImage(QRect(200,0,600,600),QImage(":/new/prefix1/background1.jpg"));
    pen.drawImage(QRect(50,270,20,20),QImage(":/new/prefix1/speed2.png"));
    pen.drawImage(QRect(50,300,20,20),QImage(":/new/prefix1/wall.png"));
    pen.drawImage(QRect(50,330,20,20),QImage(":/new/prefix1/doublescore.png"));

    //绘制地形
    QColor barriercolor(100,200,200);
    pen.setBrush(barriercolor);
    for(int i = 0;i < 10;i++)
    {
        pen.drawRect(set.barrier[i].x,set.barrier[i].y,20,20);
    }
    for(int i = 0;i < 10;i++)
    {
        pen.drawImage(QRect(set.food[i].x,set.food[i].y,20,20),QImage(":/new/prefix1/apple.png"));
    }
    pen.drawImage(QRect(set.tools[0].x,set.tools[0].y,20,20),QImage(":/new/prefix1/speed2.png"));
    pen.drawImage(QRect(set.tools[1].x,set.tools[1].y,20,20),QImage(":/new/prefix1/wall.png"));
    pen.drawImage(QRect(set.tools[2].x,set.tools[2].y,20,20),QImage(":/new/prefix1/doublescore.png"));

    //画出蛇
    if(!player.isdead)
    {
        snake::bodynode *tmp=player.head;
        while(tmp!=nullptr)
        {
            if(!player.ispink)
                pen.drawImage(QRect(tmp->x,tmp->y,20,20),QImage(":/new/prefix1/snakebody.png"));
            else pen.drawImage(QRect(tmp->x,tmp->y,20,20),QImage(":/new/prefix1/snakebody_2.png"));
            tmp=tmp->next;
        }
    }

    //蛇死亡的话画出结束界面
    else
    {
        pen.drawImage(QRect(200,0,600,600),QImage(":/new/prefix1/gameover.jpg"));
    }
}

//![4]关闭窗口
void GluttonousSnakeWindow_player1::stopGame(){
    t->stop();
    QMessageBox::StandardButton rb=QMessageBox::question(this,"HINT","Quit or not？",QMessageBox::Yes|QMessageBox::No);
    if(QMessageBox::Yes==rb)
    {
        this->close();
    }
}
//![4]

//![5]
void GluttonousSnakeWindow_player1::timerupdate()
{
    if(player.isdead) stopGame();
    else
    {

        static int timer=10;//穿墙功能的计时
        score_LCD->display(score);

        //根据蛇的长度改变定时器间隔提高蛇移动的速度
        t->setInterval(player.speed);

        //判断蛇吃到穿墙道具并倒计时
        if(player.isable)
        {
            if(timer>0)
            {
                timer--;
                score_LCD->display(timer);
            }
            else
            {
                player.isable=0;
                timer=10;
            }
        }

        //前进
        GO();

        //吃食物
        Eat();

        //判断蛇是否碰到障碍死亡
        if(!player.isable)
        {
            snake::bodynode *exa=player.head;
            int i;
            for( i=0;i<10;i++)
            {
                if(exa->x==set.barrier[i].x&&exa->y==set.barrier[i].y)
                {
                    player.isdead=1;
                    break;
                }
            }
        }

        //判断蛇是否撞到尾巴或碰到墙壁死亡
        player.life();
        update();
    }
}
//! [5]

//! [6]开始按钮的点击事件
void GluttonousSnakeWindow_player1::on_btn_begin_cliked()
{
    if(btn_pause->isEnabled()&&btn_stop->isEnabled())
    {
        t->start(player.speed);
        btn_begin->setEnabled(false);
    }
    else
    {
        if(!btn_pause->isEnabled())
        {
            btn_begin->setEnabled(false);
            btn_pause->setEnabled(true);
            t->start(player.speed);
        }
    }
}
//! [6]

//! [7]停止按钮的点击事件
void GluttonousSnakeWindow_player1::on_btn_stop_cliked()
{
    btn_stop->setEnabled(false);
    btn_pause->setEnabled(false);
    btn_begin->setEnabled(true);
    t->stop();

    //弹出是否退出游戏窗口供用户选择
    QMessageBox::StandardButton rb=QMessageBox::question(this,"HINT","Quit or not？",QMessageBox::Yes|QMessageBox::No);
    if(QMessageBox::Yes==rb)
    {
        this->close();
    }
    else
    {
        t->start(player.speed);
        btn_stop->setEnabled(true);
        btn_pause->setEnabled(true);
        btn_begin->setEnabled(false);
    }

}
//! [7]

//! [8]蛇前进
void GluttonousSnakeWindow_player1::GO()
{
    player.goahead();
}
//! [8]

//! [9]吃食物
void GluttonousSnakeWindow_player1::Eat()
{
    //吃食物
    int i;
    snake::bodynode *comp;
    for( i = 0;i < 10;i++)
    {
        if(player.head->x == set.food[i].x&&player.head->y == set.food[i].y)
        {
            player.iseat = 1;
            break;
        }
    }
    if(!player.iseat)
    {
        snake::bodynode *extra;
        extra=player.tail;
        player.tail=player.tail->prev;
        player.tail->next=nullptr;
        delete extra;
    }
    else
    {
        player.length++;
        score+=10;
        if(player.speed>=20) player.speed=player.speed-10;
        else player.speed=10;

        //生成新的食物
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        bool flag=0;
        do{
            comp=player.head;
            set.food[i].x = (qrand()%30)*20+200;
            set.food[i].y = (qrand()%30)*20;
            while(comp != nullptr)
            {
                if(comp->x == set.food[i].x&&comp->y == set.food[i].y)
                {
                    flag = 1;
                    break;
                }
                else
                    flag=0;
                comp = comp->next;

            }
            if(!flag)
            {
                for(int j = 0;j < 10;j++)
                {
                    if(set.barrier[j].x == set.food[i].x&&set.barrier[j].y == set.food[i].y)
                    {
                        flag = 1;
                        break;
                    }
                    else flag=0;
                }
            }
            if(!flag)
            {
                for(int j = 0;j < 3;j++)
                {
                    if(set.tools[j].x == set.food[i].x&&set.barrier[j].y == set.food[i].y)
                    {
                        flag = 1;
                        break;
                    }
                    else flag=0;
                }
            }
        }while(flag);
        player.iseat=0;
    }

    //吃道具
    if(player.head->x == set.tools[0].x&&player.head->y == set.tools[0].y)
    {
        player.speed+=10;
        produce(0);
    }

    if(player.head->x == set.tools[1].x&&player.head->y == set.tools[1].y)
    {
        player.isable=1;
        produce(1);
    }

    if(player.head->x == set.tools[2].x&&player.head->y == set.tools[2].y)
    {
        score+=20;
        produce(2);
    }

}
//! [9]

//! [10]生成道具位置
void GluttonousSnakeWindow_player1:: produce(int i)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    bool flag=0;
    snake::bodynode *comp;
    do{
        comp=player.head;
        set.tools[i].x = (qrand()%30)*20+200;
        set.tools[i].y = (qrand()%30)*20;
        while(comp != nullptr)
        {
            if(comp->x == set.tools[i].x&&comp->y == set.tools[i].y)
            {
                flag = 1;
                break;
            }
            else
                flag=0;
            comp = comp->next;

        }
        if(!flag)
        {
            for(int j = 0;j < 10;j++)
            {
                if(set.barrier[j].x == set.tools[i].x&&set.barrier[j].y == set.tools[i].y)
                {
                    flag = 1;
                    break;
                }
                else flag=0;
            }
        }
        if(!flag)
        {
            for(int j = 0;j < 10;j++)
            {
                if(set.tools[i].x == set.food[j].x&&set.tools[i].y == set.food[j].y)
                {
                    flag = 1;
                    break;
                }
                else flag=0;
            }
        }
    }while(flag);
}
//! [10]

//! [11]窗口类的析构函数
GluttonousSnakeWindow_player1::~GluttonousSnakeWindow_player1()
{
    this->close();
}
//! [11]
