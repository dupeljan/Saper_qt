#include "button.h"
#include "playground.h"
#include "stdlib.h"
#include "time.h"
#include <QDebug>
#include <list>
#include <QMessageBox>


playground::playground(char Alen, char Aheight, char bombs_amount, QGridLayout *Layout):
    QObject(),
    height(Aheight), len(Alen), bombAmount(bombs_amount){
    LayoutPoint = Layout;

//=====Создаем массив кнопок======
    List = new Button **[height];
    for(int i = 0; i < height; i++ ){
        List[i] = new Button * [len];
        for(int j = 0; j < len; j++){
            List[i][j] = new Button (this,i,j);
            Layout->addWidget(List[i][j] , i , j); // добавляем в массив
        }
    }
//===заполняем его бомбами=========
    srand(time(NULL));

    Button::coordType random_coord;
    if( bombs_amount <= height * len ){
        do{
            random_coord.setCoord(rand() % height , rand() % len );
            if ( ! List[random_coord.i][random_coord.j]->getBomb() ){
                List[random_coord.i][random_coord.j]->putBomb();
                bombs_amount--;
            }
        }while(bombs_amount);
    }

}

playground::~playground(){
    for(int i = 0; i < height; i++)
        for(int j = 0; j < len; j++){
            //удаляем из layoutа каждую кнопку
            LayoutPoint->removeWidget(List[i][j]);
            delete List[i][j];
        }
}
void playground::LCM(){
    Button *button = static_cast<Button*>( sender() );// получаем указатель на нажатую кнопку
    if( button &&  !button->getState() && !button->getFlag() ){ //если закрыта и нет флага
        Button::coordType coords(button->getCoord().i,button->getCoord().j);
        qDebug()<<(int)button->getCoord().i<<" "<<(int)button->getCoord().j<<"bomb"<<(int)button->getBomb();

        if( button->getBomb() ){
            button->setMyIcon(Button::bombImage);
            gameOver();
        }
        else{ //просмотрим соседние кнопки
            qDebug()<<"--------";
            char amountNearBombs = 0;
            for(int i = coords.i - 1; i <= coords.i + 1 ; i++ ) // просмотрим 3 столбца
                for( int j = coords.j - 1; j <= coords.j +1; j++) //просмотрм 3 строки
                    if( buttonIsExept(i,j) ){
                        qDebug()<<(int)i<<' '<<(int)j;
                        amountNearBombs+= (char)List[i][j]->getBomb(); //получим кол-во бомб рядом

            }
            qDebug()<<"--------";
            if (amountNearBombs)  {                                     //если бомбы есть
                button->putNumber(amountNearBombs);
                qDebug()<<(int)amountNearBombs <<'\n';

            }
            else{
                button->openButton();
                for(int i = coords.i - 1; i <= coords.i + 1 ; i++ ) // просмотрим 3 столбца
                    for( int j = coords.j - 1; j <= coords.j +1; j++) //просмотрм 3 строки
                        if( i != coords.i || j != coords.j )
                            findOut(i,j);

            }
            if (winExpect()) victory();
        }
    }
}


void playground::findOut(char ai, char aj){
    if( buttonIsExept(ai, aj) && !List[ai][aj]->getFlag()){   //нет флага
        List[ai][aj]->openButton();
        char amountNearBombs = 0;
        for(int i = ai - 1; i <= ai + 1 ; i++ ) // просмотрим 3 столбца
            for( int j = aj - 1; j <= aj +1; j++) //просмотрм 3 строки
                if( buttonIsExept(i,j) )
                    amountNearBombs+= (char)List[i][j]->getBomb(); //получим кол-во бомб рядом
        if (amountNearBombs)
            List[ai][aj]->putNumber(amountNearBombs);
        else{
            for(int i = ai - 1; i <= ai + 1 ; i++ ) // просмотрим 3 столбца
                for( int j = aj - 1; j <= aj +1; j++) //просмотрм 3 строки
                    if(i != ai || j != aj)           //исключаем вызывающую кнопочку
                        findOut(i,j);
        }
     }
}


void playground::RCM(){
    Button *button = static_cast<Button*>( sender() );// получаем указатель на нажатую кнопку
    if( button &&  !button->getState() ){
        if (!button->getFlag()){ // если флага не было - добавляем в список
            flagList.push_back(button->getCoord());
        }
        else{ //иначе удаляем из вектора эл-т с коорд button
            flagList.remove(button->getCoord());
        }
        button->changeFlag();
        //проверка на победу
        qDebug()<<"hey"<<amountOpenedButtons();

        if (winExpect()) victory();
    }
}

bool playground::winExpect(){
    if(flagList.size()  == bombAmount)           //кол-во флажков == кол-во бомб
        if(amountOpenedButtons() == bombAmount){ //кол-во открытых кнопок == кол-во бомб
            bool win = 1;
            for(std::list<Button::coordType>::iterator it = flagList.begin(); it != flagList.end() && win; it++)
                win = List[it->i][it->j]->getBomb();



            //если все кнопки с коорд из списка с бомбами - победа!
            return win;
        }
    return false;
}

bool playground::buttonIsExept(char i, char j){//если не выходит за границы и кнопка закрыта
    return (0 <= i && i < height && 0<= j && j < len && ! List[i][j]->getState())? true : false;
}

void playground::gameOver(){

    qDebug() <<"You lose";
    QMessageBox::information(0,":(","You Lose","tryAgain");
    emit replay();

}

void playground::victory(){
    qDebug()<<"UPIII";
    QMessageBox::information(0,"UPI","You Win!","tryAgain");
    qDebug()<<"hhh";
    emit replay();
}

int playground::amountOpenedButtons(){
    int ans = 0;
    for(int i = 0; i < height; i++)
        for(int j = 0; j < len; j++)
            ans += (int) ( !List[i][j]->getState() );
    return ans;
}
void playground::disable(){
    for(int i = 0; i < height; i++)
        for(int j = 0; j < len; j++)
            List[i][j]->setEnabled(false);
}
