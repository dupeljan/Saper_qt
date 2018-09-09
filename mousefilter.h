/*#ifndef MOUSEFILTER_H
#define MOUSEFILTER_H

#include <QObject>
 Класс преобразует событие:
 * нажатие ПКМ на кнопку в
 * сигнал RClicked
class MouseFilter : public QObject
{
public:
    explicit MouseFilter(QObject *parent = nullptr);

protected:
    virtual bool eventFilter(QObject* , QEvent );

signals:
    void RCliked();
};

#endif // MOUSEFILTER_H
*/
