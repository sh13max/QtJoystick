#include "joystick.h"

Joystick::Joystick(QQuickItem* parent) : QQuickPaintedItem(parent) {
    value = QPointF(0,0);
    outOfBounds = false;
    setAcceptTouchEvents(true); //Add touch event listeners
    setAcceptedMouseButtons(Qt::AllButtons); //Add all mouse event listeners
}

// Render
void Joystick::paint(QPainter *painter) {
    painter->setPen(QPen(QBrush(color),borderWidth));
    painter->setBrush(background);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawEllipse(boundingRect().adjusted(borderWidth,borderWidth,-borderWidth,-borderWidth));

    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(QRectF(QPointF(this->width() / 2 - (this->width() / 8) - value.x(),this->height() / 2 - (this->height() / 8) - value.y()),
                                QSizeF(this->width() / 4, this->height() / 4)));
}

// Output Value
qreal Joystick::getValueX() const {return value.x();}
qreal Joystick::getValueY() const {return value.y();}
QPointF Joystick::getValue() const {return value;}

// Background property
QColor Joystick::getBackground() const {return background;}
void Joystick::setBackground(QColor background) {
    if (this->background == background)
        return;
    this->background = background;
    this->update();
    emit backgroundChanged(this->background);
}

// Border & handle color property
QColor Joystick::getColor() const {return color;}
void Joystick::setColor(QColor color) {
    if (this->color == color)
        return;
    this->color = color;
    this->update();
    emit colorChanged(this->color);
}

// Border width property
qreal Joystick::getBorderWith() const {return this->borderWidth;}
void Joystick::setBorderWidth(qreal borderWidth) {
    if (qFuzzyCompare(this->borderWidth, borderWidth))
        return;
    this->borderWidth = borderWidth;
    this->update();
    emit borderWidthChanged(this->borderWidth);
}

// Events
void Joystick::mousePressEvent(QMouseEvent *event) {
    event->accept();
    startMousePosition = event->localPos();
}

void Joystick::mouseMoveEvent(QMouseEvent *event) {
    event->accept();
    QPointF endMousePosition = event->localPos();
    if(!qFuzzyCompare(value.x(),startMousePosition.x() - endMousePosition.x()))
        emit valueXChanged(startMousePosition.x() - endMousePosition.x());
    if(!qFuzzyCompare(value.y(), startMousePosition.y() - endMousePosition.y()))
        emit valueYChanged(startMousePosition.y() - endMousePosition.y());
    outOfBounds =
            !((endMousePosition.x() - startMousePosition.x()) * (endMousePosition.x() - startMousePosition.x()) +
            (endMousePosition.y() - startMousePosition.y()) * (endMousePosition.y() - startMousePosition.y()) <
            (this->width() / 2 - this->width() / 8) * (this->height() / 2 - this->height() / 8));
    if(outOfBounds){
        qreal angle = atan2(startMousePosition.y() - endMousePosition.y(), startMousePosition.x() - endMousePosition.x());
        value = QPointF(cos(angle) * (this->width() / 2 - this->width() / 8),
                        sin(angle) * (this->height() / 2 - this->height() / 8));
    } else {
        value = startMousePosition - endMousePosition;
    }
    emit valueChanged(value);
    update();
}

void Joystick::mouseReleaseEvent(QMouseEvent *event) {
    event->accept();
    startMousePosition = QPointF();
    value = QPointF(0,0);
    update();
}

