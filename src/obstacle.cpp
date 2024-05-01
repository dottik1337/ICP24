#include <QPainter>
#include "obstacle.h"
/**
 * @brief Obstacle::Obstacle Sets up obstacle
 */
Obstacle::Obstacle()
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
}

//Obstacle area for redrawing
/**
 * @brief Obstacle::boundingRect Creates rectangle for drawing purposes of the app
 * @return Redrawing rectangle
 */
QRectF Obstacle::boundingRect() const
{
    return QRectF(-size/2,-size/2,size,size);
}

// Obstacle hitbox
/**
 * @brief Obstacle::shape Creates hitbox of obstacle
 * @return Obstacle hitbox
 */
QPainterPath Obstacle::shape() const
{
    QPainterPath path;
    path.addRect(-size/2,-size/2,size,size);
    return path;
}

// Obstacle visual
/**
 * @brief Obstacle::paint Obstacle visual
 * @param painter Obstacle visual
 */
void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(Qt::blue);
    painter->drawRect(-size/2,-size/2,size,size);
}
