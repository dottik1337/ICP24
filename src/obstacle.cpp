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
    return QRectF(QPointF(x - adjust, y - adjust),
                  QPointF(x + size + adjust, y + size + adjust));
}

// Obstacle hitbox
QPainterPath Obstacle::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(x,y,size,size));
    return path;
}

// Obstacle visual
void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(Qt::blue);
    painter->drawRect(x,y,size,size);
}
