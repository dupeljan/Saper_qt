#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#include "button.h"
#include <list>
#include <QDebug>
#include <QObject>
#include <QGridLayout>

class playground : public QObject
{
    Q_OBJECT
//=====Свойства================
    Button ***List;
    char height, len, bombAmount;
    std::list<Button::coordType> flagList;
    QGridLayout *LayoutPoint;
//==============методы==========

    void gameOver();
    void findOut(char ai, char aj);
    void victory();
    bool winExpect();
    bool buttonIsExept(char i, char j);
    int amountOpenedButtons();
public:
    void disable();  // это на время
    playground(char Alen , char Aheight, char bombs_amount, QGridLayout *Layout);
    playground(){}
    ~playground();
public slots:
    void LCM();
    void RCM();
signals:
    void replay();
};

#endif // PLAYGROUND_H
