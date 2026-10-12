#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QPainterPath>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget* obj = nullptr);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MYBUTTON_H
