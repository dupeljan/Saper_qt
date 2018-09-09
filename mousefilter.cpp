/*#include <QObject>
#include <QEvent>
#include <QMouseEvent>
#include "button.h"
#include "mousefilter.h"

MouseFilter::MouseFilter(QObject *parent) : QObject(parent)
{
    connect(this,SIGNAL(RCliked()),button , SIGNAL( RCliced() ) );
}

bool MouseFilter::eventFilter(QObject *pobj , QEvent *pe ){
    if(pe->type() == QEvent::MouseButtonPress)                         //если кнопка мыши
        if(static_cast<QMouseEvent*>(pe)->button() == Qt::RightButton) //правая кнопка мыши
            if(static_cast<Button*>(pobj) ){                           //и нажали на кнопку
                //вырабатываем сигнал RClicked

            }
}
*/
