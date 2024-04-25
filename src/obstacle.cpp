#include <QPainter>
#include "obstacle.h"

Obstacle::Obstacle()
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
}

//Obstacle area for redrawing
QRectF Obstacle::boundingRect() const
{
    qreal adjust = 5;
    return QRectF(QPointF(this->x() - adjust, this->y() - adjust),
                  QPointF(this->x() + size + adjust, this->y() + size + adjust));
}

// Obstacle hitbox
QPainterPath Obstacle::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(this->x(),this->y(),size,size));
    return path;
}

// Obstacle visual
void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(Qt::blue);
    painter->drawRect(this->x(),this->y(),size,size);
}
