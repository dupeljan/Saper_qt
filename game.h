#ifndef GAME_H
#define GAME_H
#define INDENTATION 40 //отступ

/*Класс, реализующий функцию
 * "Играть заново"
 */
#include <QObject>
#include <QGridLayout>
#include "playground.h"

class game : public QObject
{
    Q_OBJECT
//==================поля========
    QGridLayout Layout;
    playground *field;
    char len, height, bombs_amount;
//============методы=============
public:
    game(char Alen, char Aheight, char Abombs_amount);
//Layouts методы
    QGridLayout* getLayout(){ return &Layout; }
    char getLen(){ return len; }
    char getHeight(){ return height; }

public slots:
    void work();
};

#endif // GAME_H
