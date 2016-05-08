#include "tictactoe.h"
#include "ui_tictactoe.h"
#include <QtGui>
#include <QPainter>
#include <QDebug>

TicTacToe::TicTacToe(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::TicTacToe)
{
    turn=0;
    myState = "---------";
    myStateT = "---------";
    V=0;
    ui->setupUi(this);
    this->setFixedSize(500,500);
    this->setWindowTitle("Tic Tac Toe");

    rects[0]=QRect(50,100,100,100);
    rects[1]=QRect(150,100,100,100);
    rects[2]=QRect(250,100,100,100);
    rects[3]=QRect(50,200,100,100);
    rects[4]=QRect(150,200,100,100);
    rects[5]=QRect(250,200,100,100);
    rects[6]=QRect(50,300,100,100);
    rects[7]=QRect(150,300,100,100);
    rects[8]=QRect(250,300,100,100);

//    lines[0]=QLine(50,150,350,150);
//    lines[1]=QLine(100,100,100,400);
//    lines[2]=QLine(50,250,350,250);
//    lines[3]=QLine(200,100,200,400);
//    lines[4]=QLine(50,350,350,350);
//    lines[5]=QLine(300,100,300,400);
//    lines[6]=QLine(50,100,350,400);
//    lines[7]=QLine(350,100,50,400);
}

TicTacToe::~TicTacToe()
{
    delete ui;
}
void TicTacToe::paintEvent(QPaintEvent *e)
{
    QPainter *p=new QPainter(this);
    p->fillRect(this->rect(),QColor("white"));
    p->setPen(QColor("black"));

    int w=this->width()/5,h=this->height()/5 ;


    p->drawRects(rects,9);

    QString dt="Turns=";
    p->drawText(20,70,dt.append(QString::number(turn)));
    for (int position = 0; position < 9; ++position) {


            if (myState.at(position) == 'x') {
                p->drawLine(rects[position].topLeft(), rects[position].bottomRight());
                p->drawLine(rects[position].topRight(), rects[position].bottomLeft());
            } else if (myState.at(position) == 'o') {
                p->drawEllipse(rects[position]);
            }

        }

    QString win="-";
    win=checkWin().toUpper();
    if(win.at(0)!='-')
    {   win.append(" Win!");
        p->drawText(20,50,win);
    }
    else if(turn==9)
    {
        win = "Draw!";
        p->drawText(20,50,win);

    }
    dt="Value=";
   p->drawText(220,50,dt.append(QString::number(MinMax())));
   dt="State=";
  p->drawText(120,50,dt.append(myState));
  dt="StateT=";
 p->drawText(120,70,dt.append(myStateT));
}
void TicTacToe::clearState()
{
    myState = "---------";
    myStateT = "---------";
    turn=0;
    update();
}

QString TicTacToe::checkWin()
{
    int t=turn;
    turn = 9;
    for(int i=0;i<3;i++)
        if(myState.at(i)==myState.at(i+3) && myState.at(i+3)==myState.at(i+6) && myState.at(i)!='-')
            return myState.at(i);

    for(int i=0;i<3;i+=2)
    {   if(i==0&&myState.at(i)==myState.at(i+4) && myState.at(i+4)==myState.at(i+8)&& myState.at(i)!='-')
            return myState.at(i);
        if(i==2&&myState.at(i)==myState.at(i+2) && myState.at(i+2)==myState.at(i+4)&& myState.at(i)!='-')
                    return myState.at(i);
    }

    for(int i=0;i<=6;i+=3)
        if(myState.at(i)==myState.at(i+1) && myState.at(i+1)==myState.at(i+2) && myState.at(i)!='-')
            return myState.at(i);

    turn=t;
    return QString('-');
}

int TicTacToe::MinMax()
{
    int val=0;
    for(int i=0;i<9;i++)
    {
        if(myStateT[i]=='x')
        {
            if(i==4)
                val+=10;
            else if(i==0||i==2||i==6||i==8)
                val+=8;
            else if(i==1||i==3||i==5||i==7)
                val+=6;
        }
        if(myStateT.at(i)=='o')
        {
            if(i==4)
                val-=10;
            if(i==0||i==2||i==6||i==8)
                val-=8;
            if(i==1||i==3||i==5||i==7)
                val-=6;
        }

    }
    return val;
}

void TicTacToe::Min()
{
    myStateT=myState;
    int i,POS;
    for( i=0;i<9;i++)
        {
            if(myState[i]=='-')
            {
                myStateT.replace(i, 1, 'o');
                int t=MinMax();
                if(t<V)
                {
                    V=t;
                    POS=i;
                }
                myStateT.replace(i, 1, '-');
            }
        }
    myState.replace(POS, 1, 'o');
    myStateT=myState;
}

void TicTacToe::Max()
{
    int i,POS,vt=0;
    myStateT=myState;
    for( i=0;i<9;i++)

            if(myState[i]=='-')
            {
               myStateT.replace(i, 1, 'x');
                int t=MinMax();
                qDebug()<<"V="<<MinMax()<<" pos="<<i<<endl;
                qDebug()<<myStateT<<endl;
                if(t>vt)
                {
                    vt=t;
                    POS=i;

                }
                myStateT.replace(i, 1, '-');
                qDebug()<<myStateT<<endl;
            }

    myState.replace(POS, 1, 'x');
    myStateT=myState;
}

void TicTacToe::mousePressEvent(QMouseEvent *e)
{
    if (turn >= 9)
            clearState();
    else
    {   if (turn % 2 == 0)
        {
            Max();
            turn++;
        }

    for (int position = 0; position < 9; ++position) {

                if (rects[position].contains(e->pos()))
                {
                    if (myState[position]=='-') {
                        //if (turn % 2 == 0)
                            //myState.replace(position, 1, 'x');
                           // Max();

                        //else
                            myState.replace(position, 1, 'o');
                        ++turn;
                    }
                }
            }
    }

    update();
}

