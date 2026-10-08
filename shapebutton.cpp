#include "shapebutton.h"
#include <QPainter>

static QPainterPath svgPath()
{
    QPainterPath p;
    p.moveTo(155, 40);
    p.lineTo(105, 40);
    // SVG arc -> Qt arcTo: çember merkezi (-14, 55.5), r = 120.
    // Qt'de açılar saat yönünün tersine pozitif, SVG sweep=1 saat yönü -> negatif sweep.
    p.arcTo(QRectF(-14.0 - 120, 55.5 - 120, 240, 240), 7.42, -67.98);
    p.lineTo(155, 160);
    p.closeSubpath();
    return p;
}

ShapeButton::ShapeButton(QWidget *parent) : QAbstractButton(parent)
{
    setText("Button");
    setAttribute(Qt::WA_Hover);
}


QPainterPath ShapeButton::scaledPath() const
{
    static const QPainterPath src = svgPath();
    const QRectF from = src.boundingRect();
    const QRectF to = QRectF(rect()).adjusted(2, 2, -2, -2); // kalınlık payı

    // En-boy oranını koruyarak widget'a sığdır ve ortala
    const qreal s = qMin(to.width() / from.width(), to.height() / from.height());
    QTransform t;
    t.translate(to.center().x(), to.center().y());
    t.scale(s, s);
    t.translate(-from.center().x(), -from.center().y());
    return t.map(src);
}

bool ShapeButton::hitButton(const QPoint &pos) const
{
    return scaledPath().contains(pos);
}

void ShapeButton::paintEvent(QPaintEvent *P)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QColor fill = m_fillColor;
    if (isDown())
        fill = fill.darker(130);
    else if (underMouse())
        fill = fill.lighter(115);

    const QPainterPath path = scaledPath();
    p.setPen(QPen(QColor("#2c2c2c"), 3.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    p.setBrush(fill);
    p.drawPath(path);

    // Sol taraf kavisli; yazıyı şeklin dolu olan sağ-alt kısmına ortala
    QRectF textRect = path.boundingRect();
    textRect.setLeft(textRect.left() + textRect.width() * 0.45);
    textRect.setTop(textRect.top() + textRect.height() * 0.3);
    p.setPen(Qt::white);
    p.drawText(textRect, Qt::AlignCenter, text());
}

QColor ShapeButton::fillColor() const
{
    return m_fillColor;
}

void ShapeButton::setFillColor(const QColor &newFillColor)
{
    m_fillColor = newFillColor;
    update(); // renk değişince yeniden çiz
}

QSize ShapeButton::sizeHint() const
{
    return QSize(120, 130);
}
