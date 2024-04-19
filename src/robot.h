#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsItem>


class Robot : public QGraphicsItem
{
public:
    Robot();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(
                QPainter *painter,
          const QStyleOptionGraphicsItem *option,
                QWidget *widget) override;


    bool rotationDirection = 0; // 0 = left, 1 = right
    qreal rotationAngle = 30; // degrees
    qreal detectionRange = 50;
    qreal speed = 1;
    qreal size = 20;


protected:
    void advance(int step) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;


private:
    int state = 0; // 0 = idle, 1 = forward, 2 = right, 3 = left
};


#endif
