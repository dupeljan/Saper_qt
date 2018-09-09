#include "game.h"
#include <QDebug>

game::game(char Alen, char Aheight, char Abombs_amount):
    len(Alen) , height(Aheight), bombs_amount(Abombs_amount)
{
    //Изменение Layout
    Layout.setHorizontalSpacing(0);
    Layout.setVerticalSpacing(0);
    //==================
    field = new playground(len,height,bombs_amount, &Layout);
    connect(field , SIGNAL(replay()), this , SLOT(work()));
}

void game::work(){


        qDebug()<<"hhh";
        disconnect(field , SIGNAL(replay()), this , SLOT(work()));
        delete field;

    field = new playground(len,height,bombs_amount, &Layout);
    connect(field , SIGNAL(replay()), this , SLOT(work()));
}
