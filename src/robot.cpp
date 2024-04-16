#include "robot.h"
#include "qevent.h"

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
    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIsSelectable);
}

QRectF Robot::boundingRect() const
{
    qreal adjust = 5;
    return QRectF(QPointF(-size - adjust, -size - adjust),
                  QPoint(size + adjust, detectionRange > size ? (detectionRange + adjust) : (size + adjust)));
}

QPainterPath Robot::shape() const
{
    QPainterPath path;
    path.addEllipse(-size/2,-size/2,size,size);
    return path;
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(isSelected() ? Qt::red : Qt::white);
    painter->drawEllipse(-size/2,-size/2,size,size);
    painter->drawLine(QLine(QPoint(0,0), QPoint(0, detectionRange)));
}

void Robot::advance(int step)
{
    if (!step)
        return;

    // find potential colisions
    const QList<QGraphicsItem *> dangerObstacle = scene()->items(QRectF(mapToScene(-size/2,0), mapToScene(size/2, detectionRange)));

    if (!isSelected())
    {
        if (dangerObstacle.size() > 1)
        {
            rotationDirection ? setRotation(rotation() - (rotationAngle * Pi)) : setRotation(rotation() + (rotationAngle * Pi));
        }
        else
        {
            setPos(mapToParent(0, speed));

        }
    }
    else
    {
        if (state == 0)
        {
            return;
        }
        else if (state == 1 && dangerObstacle.size() <= 1)
        {
            setPos(mapToParent(0, speed));
        }
        else if (state == 2)
        {
            setRotation(rotation() + (rotationAngle * Pi));
        }
        else if (state == 3)
        {
            setRotation(rotation() - (rotationAngle * Pi));
        }
    }
}


void Robot::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene* scene = this->scene();
    if (scene) {
        // Deselect all items in the scene
        QList<QGraphicsItem*> items = scene->items();
        for (QGraphicsItem* item : items) {
            item->setSelected(false);
        }

        // Select this item
        setSelected(true);
        update();
    }
    QGraphicsItem::mousePressEvent(event);
}

void Robot::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_W)
    {
        state = 1;
    }
    else if (event->key() == Qt::Key_D)
    {
        state = 2;
    }
    else if (event->key() == Qt::Key_A)
    {
        state = 3;
    }
    else if (event->key() == Qt::Key_S)
    {
        state = 0;
    }
}
