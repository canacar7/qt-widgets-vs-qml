#ifndef SHAPEBUTTON_H
#define SHAPEBUTTON_H

#include <QAbstractButton>
#include <QColor>
#include <QPainterPath>

class ShapeButton   : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor)
public:
    explicit ShapeButton(QWidget *parent = nullptr);


    QColor fillColor() const;
    void setFillColor(const QColor &newFillColor);

protected:
    void paintEvent(QPaintEvent* )  override;
    QSize sizeHint() const override;
    bool hitButton(const QPoint & pos) const override;

private:
    QColor m_fillColor = QColor("#4a90d9");
    QPainterPath scaledPath() const;
};

#endif // SHAPEBUTTON_H
