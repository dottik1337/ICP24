#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsItem>


class Robot : public QGraphicsItem
{
public:
    Robot();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;


    bool rotationDirection = 0; // 0 = left, 1 = right
    qreal rotationAngle = 0.25;
    qreal detectionRange = 50;

protected:
    void advance(int step) override;

private:
    qreal angle = 0;
    qreal speed = 0;
};


#endif
