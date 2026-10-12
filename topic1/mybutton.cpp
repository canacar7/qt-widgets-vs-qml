#include "mybutton.h"

MyButton::MyButton(QWidget *obj) : QPushButton(obj)
{
    setText("Button");
    setMinimumSize(130, 130);
}

// image/button.svg: M 155 40 L 105 40 A 120 120 0 0 1 45 160 L 155 160 Z is taken svg file.
static QPainterPath getPath()
{
    QPainterPath tPath;
    tPath.moveTo(155, 40);
    tPath.lineTo(105, 40);
    tPath.arcTo(QRectF(-14 -120, 55.5 - 120, 240, 240), 7.42, -67.98);
    tPath.lineTo(155, 160);
    tPath.closeSubpath();
    return tPath;
}
void MyButton::paintEvent(QPaintEvent *event)
{
    //1 pathi widget a koyacagiz.
    const QPainterPath tPath    = getPath();
    const QRectF       bbox    = tPath.boundingRect();
    const QRectF       adjBbox = QRectF(rect()).adjusted(2,2,-2,-2);
    const qreal        s       = qMin(adjBbox.width() / bbox.width(), adjBbox.height() / bbox.height());

    QTransform transform;
    transform.translate(adjBbox.center().x(), adjBbox.center().y());
    transform.scale(s,s);
    transform.translate(-bbox.center().x(), -bbox.center().y());

    const QPainterPath path = transform.map(tPath);

    //2 cizim
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QColor("#2c2c2c"), 3.5));
    painter.setBrush(isDown() ? QColor("#2E3135") : QColor("#3C3F44"));
    painter.drawPath(path);

    //3 yazi
    painter.setPen(Qt::white);
    painter.drawText(path.boundingRect(), Qt::AlignCenter, text());
}
