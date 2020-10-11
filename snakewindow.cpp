#include "snakewindow.h"

//![1]snakewindow类的构造函数
snakewindow::snakewindow()
{
    //生成按钮
    btn_begin->setParent(this);
    btn_begin->setText("BEGIN");
    btn_begin->resize(100,50);
    btn_begin->move(50,30);

    btn_pause->setParent(this);
    btn_pause->setText("PAUSE");
    btn_pause->resize(100,50);
    btn_pause->move(50,110);

    btn_stop->setParent(this);
    btn_stop->setText("STOP");
    btn_stop->resize(100,50);
    btn_stop->move(50,190);

    btn_begin->setStyleSheet("QPushButton{ \
                                         border: 0px solid;\
                                         background-color:#B2DFEE;\
                                         color:#FFFFFF;\
                                         border-radius: 20px;\
                                     }\
                                      QPushButton:disabled{\
                                         background-color:#DCDCDC;\
                                         border-radius:20px;\
                                         color:#FFFFFF;    \
                                     }\
                                     QPushButton:hover{\
                                         border: 0px solid;\
                                         background-color:#C1FFC1;\
                                         border-radius:20px;\
                                         color:#FFFFFF;\
                                         opacity:0.2;\
                                     }\
                                     QPushButton:pressed{\
                                         background-color:#54FF9F;\
                                         border-radius:20px;\
                                         color:#FFFFFF;    \
                        }");
    btn_pause->setStyleSheet("QPushButton{ \
                                         border: 0px solid;\
                                         background-color:#B2DFEE;\
                                         color:#FFFFFF;\
                                         border-radius: 20px;\
                                     }\
                                      QPushButton:disabled{\
                                         background-color:#DCDCDC;\
                                         border-radius:20px;\
                                         color:#FFFFFF;    \
                                     }\
                                     QPushButton:hover{\
                                         border: 0px solid;\
                                         background-color:#C1FFC1;\
                                         border-radius:20px;\
                                         color:#FFFFFF;\
                                         opacity:0.2;\
                                     }\
                                     QPushButton:pressed{\
                                         background-color:#54FF9F;\
                                         border-radius:20px;\
                                         color:#FFFFFF;    \
                        }");

    btn_stop->setStyleSheet("QPushButton{ \
                                         border: 0px solid;\
                                         background-color:#B2DFEE;\
                                         color:#FFFFFF;\
                                         border-radius: 20px;\
                                     }\
                                      QPushButton:disabled{\
                                         background-color:#DCDCDC;\
                                         border-radius:20px;\
                                         color:#FFFFFF;    \
                                     }\
                                     QPushButton:hover{\
                                         border: 0px solid;\
                                         background-color:#C1FFC1;\
                                         border-radius:20px;\
                                         color:#FFFFFF;\
                                         opacity:0.2;\
                                     }\
                                     QPushButton:pressed{\
                                         background-color:#54FF9F;\
                                         border-radius:20px;\
                                         color:#FFFFFF;    \
                        }");

    //按钮的槽函数
    connect(btn_begin,&QPushButton::clicked,this,&snakewindow::on_btn_begin_cliked);
    connect(btn_pause,&QPushButton::clicked,this,&snakewindow::on_btn_pause_cliked);
    connect(btn_stop,&QPushButton::clicked,this,&snakewindow::on_btn_stop_cliked);  

    //文本框显示“SCORE”
    sc=new QLabel(this);
    QFont sc_font;
    sc_font.setPointSize(18);
    sc->setFont(sc_font);
    sc->setText("SCORE:");
    sc->setGeometry(QRect(50,390,100,20));
    sc->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    //显示屏显示玩家得分
    score_LCD = new QLCDNumber(this);
    score_LCD->setDigitCount(4);
    score_LCD->resize(100,80);
    score_LCD->setMode(QLCDNumber::Dec);
    score_LCD->setSegmentStyle(QLCDNumber::Flat);
    score_LCD->move(50,420);
    score_LCD->display(0);

    //定时器
    t=new QTimer(this);
    connect(t,SIGNAL(timeout()),this,SLOT(update()));

    setWindowTitle("Snake War");
    resize(800, 600);
}
//! [1]

//! [2]开始按钮点击事件的槽函数
void snakewindow::on_btn_begin_cliked()
{
    if(btn_pause->isEnabled()&&btn_stop->isEnabled())
    {
        t->start(speed);
        btn_begin->setEnabled(false);
    }
    else
    {
        if(!btn_pause->isEnabled())
        {
            btn_begin->setEnabled(false);
            btn_pause->setEnabled(true);
            t->start();
        }
    }
}
//! [2]

//! [3]暂停按钮点击事件的槽函数
void snakewindow::on_btn_pause_cliked()
{
    btn_pause->setEnabled(false);
    btn_begin->setEnabled(true);
    t->stop();
}
//! [3]

//! [4]停止按钮点击事件的槽函数
void snakewindow::on_btn_stop_cliked()
{
    btn_stop->setEnabled(false);
    btn_pause->setEnabled(false);
    btn_begin->setEnabled(true);
    t->stop();

    //弹出是否关闭的选择窗口
    QMessageBox::StandardButton rb=QMessageBox::question(this,"HINT","Quit or not？",QMessageBox::Yes|QMessageBox::No);
    if(QMessageBox::Yes==rb)
    {
        this->close();
    }
    else
    {
        t->start(speed);
        btn_stop->setEnabled(true);
        btn_pause->setEnabled(true);
        btn_begin->setEnabled(false);
    }
}
//! [4]
