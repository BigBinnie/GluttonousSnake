#include "position.h"

//![1]构造函数
position::position()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    //生成障碍的位置
    for(int i=0;i<10;i++)
    {
        bool barrierbuildflag=0;
        do{
            barrier[i].x=(qrand()%30)*20+200;
            barrier[i].y=(qrand()%30)*20;
            //比较与之前生成障碍的位置
            if(i!=0)
            {
                for(int j=0;j<i;j++)
                {
                    if(barrier[i].x==barrier[j].x&&barrier[i].y==barrier[j].y)
                    {   barrierbuildflag=1;
                        break;
                    }
                    else barrierbuildflag=0;
                }
            }
            else barrierbuildflag=0;
            //避免生成在蛇的初始位置
            if(!barrierbuildflag)
            {
                if((barrier[i].x==0&&barrier[i].y==0)||(barrier[i].x==0&&barrier[i].y==20)||(barrier[i].x==780&&barrier[i].y==0)||(barrier[i].x==780&&barrier[i].y==20))
                    barrierbuildflag=1;
                else barrierbuildflag=0;
            }
        }while(barrierbuildflag);
    }

    //生成食物的位置
    for(int i=0;i<10;i++)
    {
        bool foodbuildflag=0;
        do{
            food[i].x=(qrand()%30)*20+200;
            food[i].y=(qrand()%30)*20;
            //比较与之前生成食物的位置
            if(i!=0)
            {
                for(int j=0;j<i;j++)
                {
                    if(food[i].x==food[j].x&&food[i].y==food[j].y)
                    {
                        foodbuildflag=1;
                        break;
                    }
                    else foodbuildflag=0;
                }
            }
            else foodbuildflag=0;
            //比较与障碍的位置
            if(!foodbuildflag)
            {
                for(int j=0;j<10;j++)
                {
                    if(barrier[j].x==food[i].x&&barrier[j].y==food[i].y)
                    {
                        foodbuildflag=1;
                        break;
                    }
                    else foodbuildflag=0;
                }
            }
            if(!foodbuildflag)
            {

                if((food[i].x==0&&food[i].y==0)||(food[i].x==0&&food[i].y==20)||(food[i].x==780&&food[i].y==0)||(food[i].x==780&&food[i].y==20))
                    foodbuildflag=1;

                else foodbuildflag=0;
            }
        }while(foodbuildflag);
    }

    //生成道具的位置
    for(int i=0;i<3;i++){
        bool toolbuildflag=0;
        do{
            //随机数生成道具
            tools[i].x=(qrand()%30)*20+200;
            tools[i].y=(qrand()%30)*20;

            //比较与之前生成道具的位置
            if(i!=0)
            {
                for(int j=0;j<i;j++){
                    if(tools[i].x==tools[j].x&&tools[i].y==tools[j].y)
                    {
                        toolbuildflag=1;
                        break;
                    }
                    else toolbuildflag=0;
                }
            }
            else toolbuildflag=0;
            //比较与障碍物的位置
            if(toolbuildflag!=1)
            {
                for(int j=0;j<10;j++)
                {
                    if(barrier[j].x==tools[i].x&&barrier[j].y==tools[i].y)
                    {
                        toolbuildflag=1;
                        break;
                    }
                    else toolbuildflag=0;
                }
            }
            //比较与食物的位置
            if(toolbuildflag!=1)
            {
                for(int j=0;j<10;j++)
                {
                    if(food[j].x==tools[i].x&&food[j].y==tools[i].y)
                    {
                        toolbuildflag=1;
                        break;
                    }
                    else toolbuildflag=0;
                }
            }
            //避免生成在蛇的初始位置
            if(toolbuildflag!=1)
            {
                if((tools[i].x==0&&tools[i].y==0)||(tools[i].x==0&&tools[i].y==20)||(tools[i].x==780&&tools[i].y==0)||(tools[i].x==780&&tools[i].y==20))
                    toolbuildflag=1;
                else toolbuildflag=0;
            }
        }while(toolbuildflag);
    }

}
//![1]
