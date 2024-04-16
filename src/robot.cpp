#include "robot.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}


Robot::Robot()
{
    setRotation(QRandomGenerator::global()->bounded(360 * 16));
}

QRectF Robot::boundingRect() const
{
    return QRectF(QPointF(-10, -10),
                  QPoint(20, 20));
}

QPainterPath Robot::shape() const
{
    QPainterPath path;
    path.addEllipse(-5,-5,10,10);
    return path;
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(Qt::white);
    painter->drawEllipse(-5,-5,10,10);
    painter->drawLine(QLine(QPoint(0,0), QPoint(0, detectionRange)));
}

void Robot::advance(int step)
{
    if (!step)
        return;

    // find potential colisions
    const QList<QGraphicsItem *> dangerObstacle = scene()->items(QRectF(mapToScene(-5,0), mapToScene(5, detectionRange)));


    if (dangerObstacle.size() > 1)
    {

        angle = (rotationDirection ? rotationAngle : -rotationAngle);
        setRotation(rotation() + angle * TwoPi);

    }
    else
    {
        speed = 5;
        setPos(mapToParent(0, speed));
    }


}

