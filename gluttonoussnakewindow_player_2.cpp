#include "gluttonoussnakewindow_player_2.h"

//! [1]贪吃蛇窗口类的构造函数
GluttonousSnakeWindow_player2::GluttonousSnakeWindow_player2()
{
    //在游戏窗口左侧显示两个玩家的得分
    sc1=new QLabel(this);
    QFont sc_font1;
    sc_font1.setPointSize(18);
    sc1->setFont(sc_font1);
    sc1->setText("PLAYER 1:");
    sc1->setGeometry(QRect(50,270,100,20));
    sc1->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    sc->setText("PLAYER 2:");

    score_LCD_1= new QLCDNumber(this);
    score_LCD_1->setDigitCount(4);
    score_LCD_1->resize(100,80);
    score_LCD_1->setMode(QLCDNumber::Dec);
    score_LCD_1->setSegmentStyle(QLCDNumber::Flat);
    score_LCD_1->move(50,300);

    player_2.head->x=780;
    player_2.head->y=20;
    player_2.tail->x=780;
    player_2.tail->y=0;

    t=new QTimer(this);
    connect(t,SIGNAL(timeout()),this,SLOT(timeUpdate()));
}
//! [1]

//! [2]键盘敲击事件
void GluttonousSnakeWindow_player2::keyPressEvent(QKeyEvent *ev)
{
    //player_1的键位
    if(ev->key() == Qt::Key_W)
    {
        if(player_1.direction!=1)
            player_1.direction = 0;
    }
    if(ev->key() == Qt::Key_S)
    {
        if(player_1.direction!=0)
            player_1.direction = 1;
    }
    if(ev->key() == Qt::Key_A)
    {
        if(player_1.direction!=3)
            player_1.direction = 2;
    }
    if(ev->key() == Qt::Key_D)
    {
        if(player_1.direction!=2)
            player_1.direction = 3;
    }
    //player_2的键位
    if(ev->key() == Qt::Key_Up)
    {
        if(player_2.direction!=1)
            player_2.direction = 0;
    }
    if(ev->key() == Qt::Key_Down)
    {
        if(player_2.direction!=0)
            player_2.direction = 1;
    }
    if(ev->key() == Qt::Key_Left)
    {
        if(player_2.direction!=3)
            player_2.direction = 2;
    }
    if(ev->key() == Qt::Key_Right)
    {
        if(player_2.direction!=2)
            player_2.direction = 3;
    }
}
//! [2]

//! [3]渲染事件
void GluttonousSnakeWindow_player2::paintEvent(QPaintEvent*p)
{
    QPainter pen(this);

    //绘制游戏背景图案
    pen.drawImage(QRect(200,0,600,600),QImage(":/new/prefix1/background1.jpg"));

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

    //画出蛇
    if(!player_1.isdead&&!player_2.isdead)
    {
        snake::bodynode *tmp1=player_1.head;
        while(tmp1!=nullptr)
        {
            pen.drawImage(QRect(tmp1->x,tmp1->y,20,20),QImage(":/new/prefix1/snakebody.png"));
            tmp1=tmp1->next;
        }

        snake::bodynode *tmp2=player_2.head;
        while(tmp2!=nullptr)
        {
            pen.drawImage(QRect(tmp2->x,tmp2->y,20,20),QImage(":/new/prefix1/snakebody_2.png"));
            tmp2=tmp2->next;
        }
    }

    //蛇死亡的话画出结束界面
    else
    {
        pen.drawImage(QRect(200,0,600,600),QImage(":/new/prefix1/gameover.jpg"));
    }
}

//! [3]窗口更新
void GluttonousSnakeWindow_player2::timeUpdate(){
    if(player_1.isdead||player_2.isdead) StopGame();
    else{

        score_LCD_1->display(score_1);
        score_LCD->display(score_2);

        //根据目前方向令蛇前进
        DGo();

        //player_1吃食物事件
        DEat(player_1,score_1);

        //player_2吃食物事件
        DEat(player_2,score_2);

        //判断蛇是否碰到障碍死亡
        snake::bodynode *exa1=player_1.head;
        int i;
        for( i=0;i<10;i++)
        {
            if(exa1->x==set.barrier[i].x&&exa1->y==set.barrier[i].y)
            {
                player_1.isdead=1;
                break;
            }
        }
        snake::bodynode *exa2=player_2.head;
        for( i=0;i<10;i++)
        {
            if(exa2->x==set.barrier[i].x&&exa2->y==set.barrier[i].y)
            {
                player_2.isdead=1;
                break;
            }
        }

        //判断蛇是否撞到尾巴或碰到墙壁死亡
        player_1.life();
        player_2.life();

        //判断两蛇相撞，头撞到对方的蛇死亡
        snake::bodynode *t1=player_1.head;
        snake::bodynode *t2=player_2.head;
        while(t2!=nullptr)
        {
            if(t2->next!=nullptr&&t1->x==t2->x&&t1->y==t2->y)
            {
                player_1.isdead=1;
                break;
            }
            t2=t2->next;
        }
        t2=player_2.head;
        while(t1!=nullptr)
        {
            if(t1->next!=nullptr&&t2->x==t1->x&&t2->y==t1->y)
            {
                player_2.isdead=1;
                break;
            }
            t1=t1->next;
        }

        update();
    }
}
//! [3]

//! [4]停止游戏
void GluttonousSnakeWindow_player2::StopGame()
{
    t->stop();
    if(player_1.isdead)
    {
        if(score_1>score_2) player_1.isable=1;
        else player_2.isable=1;
    }

    if(player_2.isdead)
    {
        if(score_2>score_1) player_2.isable=1;
        else player_1.isable=1;
    }
    if(player_1.isable)
    {
        QMessageBox::StandardButton rb=QMessageBox::question(this,"HINT","Player_1 win! Quit or not？",QMessageBox::Yes|QMessageBox::No);
        if(QMessageBox::Yes==rb)
        {
            this->close();
        }
    }
    else
    {
        QMessageBox::StandardButton rb=QMessageBox::question(this,"HINT","Player_2 win! Quit or not？",QMessageBox::Yes|QMessageBox::No);
        if(QMessageBox::Yes==rb)
        {
            this->close();
        }
    }
}

//! [5]计时器开始时蛇前进事件
void GluttonousSnakeWindow_player2::DGo()
{
    player_1.goahead();
    player_2.goahead();
}
//! [5]

//! [6]蛇吃食物事件
void GluttonousSnakeWindow_player2::DEat(snake &p,int &score)
{
    int i;
    snake::bodynode *comp1;
    snake::bodynode *comp2;
    for( i = 0;i < 10;i++)
    {
        if(p.head->x == set.food[i].x&&p.head->y == set.food[i].y)
        {
            p.iseat = 1;
            break;
        }
    }
    if(!p.iseat)
    {
        snake::bodynode *extra;
        extra=p.tail;
        p.tail=p.tail->prev;
        p.tail->next=nullptr;
        delete extra;
    }
    else
    {
        p.length++;
        if(p.speed>=20) p.speed=300-p.length*10;
        else p.speed=10;

        //生成新的食物
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        bool flag=0;
        do{
            comp1=player_1.head;
            comp2=player_2.head;
            set.food[i].x = (qrand()%30)*20+200;
            set.food[i].y = (qrand()%30)*20;
            while(comp1 != nullptr)
            {
                if(comp1->x == set.food[i].x&&comp1->y == set.food[i].y)
                {
                    flag = 1;
                    break;
                }
                else flag = 0;
                comp1 = comp1->next;
            }
            if(!flag)
            {
                while(comp2 != nullptr)
                {
                    if(comp2->x == set.food[i].x&&comp2->y == set.food[i].y)
                    {
                        flag = 1;
                        break;
                    }
                    else flag = 0;
                    comp2 = comp2->next;
                }
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
                    else flag = 0;
                }
            }
        }while(flag);
        p.iseat=0;
        score+=10;
    }

}
//! [6]
