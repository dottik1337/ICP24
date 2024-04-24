#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsItem>

class Obstacle : public QGraphicsItem
{
public:
    Obstacle();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(
                QPainter *painter,
          const QStyleOptionGraphicsItem *option,
                QWidget *widget) override;

    qreal size = 10;
    qreal x = 0;
    qreal y = 0;
};

#endif // OBSTACLE_H
