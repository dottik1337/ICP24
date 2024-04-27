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
    return QRectF(-size/2,-size/2,size,size);
}

// Obstacle hitbox
QPainterPath Obstacle::shape() const
{
    QPainterPath path;
    path.addRect(-size/2,-size/2,size,size);
    return path;
}

// Obstacle visual
void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(Qt::blue);
    painter->drawRect(-size/2,-size/2,size,size);
}
