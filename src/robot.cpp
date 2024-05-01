#include "robot.h"
#include "qevent.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>


#define ROTATIONSPEED 1

Robot::Robot()
{
    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);

}

// Robot area for redrawing
QRectF Robot::boundingRect() const
{
    qreal adjust = 5;
    return QRectF(QPointF(-size - adjust, -size - adjust),
                  QPoint(size + adjust, detectionRange > size/2 ? detectionRange + adjust : size + adjust));
}

// Robot hitbox
QPainterPath Robot::shape() const
{
    QPainterPath path;
    path.addEllipse(-size/2,-size/2,size,size);
    return path;
}

// Robot visual
void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(isSelected() ? Qt::red : Qt::white);
    painter->drawEllipse(-size/2,-size/2,size,size);
    // TEMP draw robot direction
    painter->drawLine(QLine(QPoint(0,0), QPoint(0, detectionRange)));
}

// Animate Robots
void Robot::advance(int step)
{
    if (!step)
        return;

    // Colision detection
    QList<QGraphicsItem *> dangerObstacle = scene()->items(QRectF(mapToParent(-size, 0), mapToParent(size, detectionRange)));
    dangerObstacle.removeOne(this);

    // Is automatic robot
    if (!isSelected() && !hasFocus())
    {
        if ( finRotation != this->rotation())
        {
            rotationDirection ? setRotation(rotation() - ROTATIONSPEED) : setRotation(rotation() + ROTATIONSPEED);
        }

        else
        {
            if (dangerObstacle.size() != 0)
            {
                rotationDirection ? finRotation -= rotationAngle : finRotation+= rotationAngle;
            }
            else
            {
                setPos(mapToParent(0, speed));

            }
        }
    }
    // Manual robot
    else
    {
        if (state == 0)
        {
            return;
        }
        else if (state == 1 && dangerObstacle.size() == 0)
        {
            setPos(mapToParent(0, speed));
        }
        else if (state == 2)
        {
            setRotation(rotation() + (ROTATIONSPEED));
        }
        else if (state == 3)
        {
            setRotation(rotation() - (ROTATIONSPEED));
        }
    }
}


// Selecting robot for manual control
void Robot::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene* scene = this->scene();
    if (scene) {
        // Deselect all items in the scene
        QList<QGraphicsItem*> items = scene->items();
        for (QGraphicsItem* item : items) {
            item->setSelected(false);
            item->clearFocus();

        }

        // Select this item
        setSelected(true);
        this->setFocus(Qt::OtherFocusReason);
        update();
    }
    QGraphicsItem::mousePressEvent(event);
}

// Manual controls on keyboard
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
