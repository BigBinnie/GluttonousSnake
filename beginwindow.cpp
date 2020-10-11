#include "beginwindow.h"

//! [1] BeginWindow的构造函数
BeginWindow::BeginWindow()
{
    setWindowTitle("Snake War");
    resize(800, 600);

    //绘制按钮
    btn1->setStyleSheet("QPushButton{ \
                                         border: 0px solid;\
                                         background-color:#EEEE00;\
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
                                         background-color:#f67469;\
                                         border-radius:20px;\
                                         color:#FFFFFF;\
                                         opacity:0.2;\
                                     }\
                                     QPushButton:pressed{\
                                         background-color:#c44237;\
                                         border-radius:20px;\
                                         color:#FFFFFF;    \
                        }");
    btn2->setStyleSheet("QPushButton{ \
                                     border: 0px solid;\
                                     background-color:#C0FF3E;\
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
                                     background-color:#f67469;\
                                     border-radius:20px;\
                                     color:#FFFFFF;\
                                     opacity:0.2;\
                                 }\
                                 QPushButton:pressed{\
                                     background-color:#c44237;\
                                     border-radius:20px;\
                                     color:#FFFFFF;    \
                    }");
    btn3->setStyleSheet("QPushButton{ \
                                         border: 0px solid;\
                                         background-color:#FF4500;\
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
                                         background-color:#f67469;\
                                         border-radius:20px;\
                                         color:#FFFFFF;\
                                         opacity:0.2;\
                                     }\
                                     QPushButton:pressed{\
                                         background-color:#c44237;\
                                         border-radius:20px;\
                                         color:#FFFFFF;    \
                        }");

    QFont s1_font;
    s1_font.setPointSize(18);

    btn1->setParent(this);
    btn1->setText("SINGAL PLAYER");
    btn1->resize(150,80);
    btn1->move(325,180);
    btn1->setFlat(0);
    btn1->setFont(s1_font);

    btn2->setParent(this);
    btn2->setText("DOUBLE PLAYER");
    btn2->resize(150,80);
    btn2->move(325,290);
    btn2->setFont(s1_font);

    btn3->setParent(this);
    btn3->setText("AI SNAKE");
    btn3->resize(150,80);
    btn3->move(325,400);
    btn3->setFont(s1_font);

    //绘制欢迎文本框
    s=new QLabel(this);
    s->setText("  Welcome To Snake War !");
    s->setGeometry(QRect(250,100,300,40));
    s->setStyleSheet("background-color: #FFC0CB;font-size:25px;color:black");
    s->setFrameShape (QFrame::Box);
    s->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    //定时器
    t=new QTimer(this);
    connect(t,SIGNAL(timeout()),this,SLOT(update()));

    connect(btn1,&QPushButton::clicked,this,&BeginWindow::on_btn1_cliked);
    connect(btn2,&QPushButton::clicked,this,&BeginWindow::on_btn2_cliked);
    connect(btn3,&QPushButton::clicked,this,&BeginWindow::on_btn3_cliked);

}
//! [1]

//! [2]渲染事件
void BeginWindow::paintEvent(QPaintEvent *p)
{
    QPainter pen(this);
    pen.drawImage(QRect(0,0,800,600),QImage(":/new/prefix1/begin.jpg"));
}
//! [2]

//! [3]生成一个单人模式对象
void BeginWindow::on_btn1_cliked()
{
    p1=new GluttonousSnakeWindow_player1;

    //弹出颜色选择框
    QMessageBox box(QMessageBox::Information, "Setting"," what snake color do you like？");
    box.setStandardButtons(QMessageBox::Ok | QMessageBox::No|QMessageBox::Cancel);
    box.setButtonText(QMessageBox::Ok, QString("Green"));
    box.setButtonText(QMessageBox::No, QString("Pink"));
    box.setButtonText(QMessageBox::Cancel, QString("Cancel"));
    QPixmap t(":/new/prefix1/beginpicture.jpg");
    QPixmap picture=t.scaled(200,210);
    box.setIconPixmap(picture);
    box.setStyleSheet(
            "QPushButton {"
                            "background-color:#89AFDE;"
                            " border-style: outset;"
                            " border-width: 5px;"
                            " border-radius: 16px;"
                            " border-color: beige;"
                            " font: bold 15px;"
                            " min-width: 5em;"
                            " min-height: 2em;"
                            "}"
            "QLabel { min-width: 7em;min-height:8em;font:24px;background-color:#f0f0f0;}"
        );

    int button = box.exec();
    if (button == QMessageBox::Ok)
        p1->player.ispink=0;
    else if(button == QMessageBox::No)
        p1->player.ispink=1;
    else return;

    p1->show();
}
//! [3]

//! [4]生成一个双人模式对象
void BeginWindow::on_btn2_cliked()
{
    p2=new GluttonousSnakeWindow_player2;

    //弹出速度选择框
    QMessageBox box(QMessageBox::Information, "Setting"," What the speed do you like？");
    box.setStandardButtons(QMessageBox::Ok | QMessageBox::No|QMessageBox::Cancel);
    box.setButtonText(QMessageBox::Ok, QString("Slow"));
    box.setButtonText(QMessageBox::No, QString("Fast"));
    box.setButtonText(QMessageBox::Cancel, QString("Cancel"));
    QPixmap t(":/new/prefix1/beginpicture.jpg");
    QPixmap picture=t.scaled(200,210);
    box.setIconPixmap(picture);
    box.setStyleSheet(
            "QPushButton {"
                            "background-color:#89AFDE;"
                            " border-style: outset;"
                            " border-width: 5px;"
                            " border-radius: 16px;"
                            " border-color: beige;"
                            " font: bold 15px;"
                            " min-width: 5em;"
                            " min-height: 2em;"
                            "}"
            "QLabel { min-width: 7em;min-height:8em;font:24px;background-color:#f0f0f0;}"
        );

    int button = box.exec();
    if (button == QMessageBox::Ok) p2->speed=400;
    else if(button == QMessageBox::No) p2->speed=200;
    else return;

    p2->show();
}
//! [4]

//! [5]生成一个AI蛇模式对象
void BeginWindow::on_btn3_cliked()
{
    p3=new AISnakeWindow;

    //弹出彩蛋框
    QMessageBox box(QMessageBox::Question, "Setting","是否为TADong打call？");
    box.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
    box.setButtonText(QMessageBox::Ok, QString("残忍拒绝"));
    box.setButtonText(QMessageBox::No, QString("疯狂打call"));
    QPixmap t(":/new/prefix1/dmk.png");
    QPixmap picture=t.scaled(200,210);
    box.setIconPixmap(picture);
    box.setStyleSheet(
            "QPushButton {"
                            "background-color:#89AFDE;"
                            " border-style: outset;"
                            " border-width: 5px;"
                            " border-radius: 16px;"
                            " border-color: beige;"
                            " font: bold 15px;"
                            " min-width: 6em;"
                            " min-height: 2em;"
                            "}"
            "QLabel { min-width:8em;min-height:8em;font:24px;background-color:#f0f0f0;}"
        );

    int button = box.exec();
    if (button == QMessageBox::No) p3->speed=50;
    else p3->speed=100;

    p3->show();
}
//! [5]
