#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QQuickPaintedItem>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QPainter>

#include <cmath>

class Joystick : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(qreal valueX READ getValueX NOTIFY valueXChanged)
    Q_PROPERTY(qreal valueY READ getValueY NOTIFY valueYChanged)
    Q_PROPERTY(QPointF value READ getValue NOTIFY valueChanged)
    Q_PROPERTY(QColor background READ getBackground WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal borderWidth READ getBorderWith WRITE setBorderWidth NOTIFY borderWidthChanged)
public:
    explicit Joystick(QQuickItem* parent = nullptr);

    void paint(QPainter *painter) override;
    qreal getValueX() const;
    qreal getValueY() const;
    QColor getBackground() const;
    QColor getColor() const;
    qreal getBorderWith() const;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    QPointF getValue() const;

signals:
    void valueXChanged(qreal valueX);
    void valueYChanged(qreal valueY);
    void backgroundChanged(QColor background);
    void colorChanged(QColor color);

    void borderWidthChanged(qreal borderWidth);

    void valueChanged(QPointF value);

public slots:
    void setBackground(QColor background);
    void setColor(QColor color);
    void setBorderWidth(qreal borderWidth);

private:
    QPointF value;
    QColor background;
    QColor color;
    qreal borderWidth;
    bool outOfBounds;

    QPointF startMousePosition;
};

#endif // JOYSTICK_H
