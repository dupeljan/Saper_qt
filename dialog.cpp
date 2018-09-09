#include "dialog.h"
#include "ui_dialog.h"
#include "playground.h"
#include "button.h"

Dialog::Dialog(QWidget *parent, game *g) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->widget->setLayout( g->getLayout() );

    //меняем размер, чтобы всё было красиво
    ui->widget->setGeometry(10,10, BUTTON_SIZE * g->getLen() + INDENTATION
                              , BUTTON_SIZE * g->getHeight() + INDENTATION);

}

Dialog::~Dialog()
{
    delete ui;
}
