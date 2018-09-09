#include "button.h"
#include <QSize>

Button::Button(QObject *mind, char i, char j): QPushButton(),
    open(0) , bomb(0) , flag(0), coord(i,j)  {
    setMyIcon( hideImage);
    //Изменение размера кнопок
    setIconSize( *( new QSize(BUTTON_SIZE,BUTTON_SIZE) ) );
    setMinimumSize(BUTTON_SIZE,BUTTON_SIZE);
    setMaximumSize(BUTTON_SIZE,BUTTON_SIZE);
    //============================
    connect(this, SIGNAL(pressed()), mind , SLOT(LCM()) );
    connect( this,SIGNAL(RClicked()),mind , SLOT(RCM()) );
}

void Button::setMyIcon(IconType control){
    QPixmap *Icon = new QPixmap;  // временная переменная
    switch (control) {
    case bombImage: Icon->load(":/icons/saper/bomb.png"); break;
    case flagImage: Icon->load(":/icons/saper/flag.png"); break;
    case hideImage: Icon->load(":/icons/saper/hide.png"); break;
    case openImage: Icon->load(":/icons/saper/open.png"); break;
    }
    setIcon(*Icon);
}

void Button::putNumber(char num){
    openButton();
    QPixmap *Icon = new QPixmap;  // временная переменная
    switch ((int)num) {
    case 1: Icon->load(":/icons/saper/1.png");break;
    case 2: Icon->load(":/icons/saper/2.png");break;
    case 3: Icon->load(":/icons/saper/3.png");break;
    case 4: Icon->load(":/icons/saper/4.png");break;
    case 5: Icon->load(":/icons/saper/5.png");break;
    case 6: Icon->load(":/icons/saper/6.png");break;
    case 7: Icon->load(":/icons/saper/7.png");break;
    case 8: Icon->load(":/icons/saper/8.png");break;
    }
    setIcon(*Icon);
}

//Обработка нажатий кнопок
/*virtual*/ void Button::mousePressEvent(QMouseEvent *e){
    if( e->button() == Qt::RightButton)
        emit RClicked();
    else
        if (e->button() == Qt::LeftButton)
            emit pressed();
}
