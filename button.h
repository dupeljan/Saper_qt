#ifndef BUTTON_H
#define BUTTON_H
#define BUTTON_SIZE 30

#include <QPushButton>
#include <QPixmap>
#include <QString>
#include <QObject>
#include <QMouseEvent>

class Button : public QPushButton
{
    Q_OBJECT
public:
    enum IconType{ bombImage , flagImage , hideImage, openImage };
    class coordType{
    public:
        bool operator ==(const coordType &x){
            return ( i == x.i && j == x.j )? true : false;
        }
        char i,j;
        coordType(char ai = 0, char aj = 0){ i = ai; j = aj; }
        void setCoord(char ai = 0, char aj = 0){ i = ai; j = aj; }
    };
private:
//===========Свойства==============================
    coordType coord;//Координаты
    bool open, bomb, flag; //присутствие||осутсвие флага || бомбы
                            //кнопка открыта||закрыта

//==========Методы==================================
protected:
    virtual void mousePressEvent(QMouseEvent *e);
public:
    //get
    coordType getCoord(){ return coord; }
    bool  getBomb() { return bomb; }
    bool  getFlag() { return flag; }
    bool  getState(){ return open;}

    //set
    void  putBomb() { bomb = true; }
    void  openButton(){ open = true;
                        setMyIcon(openImage);    }
    void  changeFlag() {
        if (flag) setMyIcon(hideImage);
        else setMyIcon(flagImage);
        flag =!flag;
    }
    void  putNumber(char num);
    void setMyIcon(IconType control);
public:
    Button(QObject *mind, char i, char j );
signals:
    void RClicked();
};
#endif // BUTTON_H
