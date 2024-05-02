/**
 * @file robot.cpp
 * @author Zdeněk Šťastný (xstast41@stud.fit.vutbr.cz)
 * @author Jozef Gallo (xgallo06@stud.fit.vutbr.cz)
 * @brief Implementation of Robot class
 * @version 0.1
 * @date 2024-05-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "robot.h"
#include "qevent.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>


#define ROTATIONSPEED 1

/**
 * @brief Robot::Robot Sets up robot
 */
Robot::Robot()
{
    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);

}

// Robot area for redrawing
/**
 * @brief Robot::boundingRect Creates rectangle for drawing purposes of the app
 * @return  Redrawing rectangle
 */
QRectF Robot::boundingRect() const
{
    qreal adjust = 5;
    return QRectF(QPointF(-size - adjust, -size - adjust),
                  QPoint(size + adjust, detectionRange > size/2 ? detectionRange + adjust : size + adjust));
}

// Robot hitbox
/**
 * @brief Robot::shape Creates hitbox of robot
 * @return Robot hitbox
 */
QPainterPath Robot::shape() const
{
    QPainterPath path;
    path.addEllipse(-size/2,-size/2,size,size);
    return path;
}

// Robot visual
/**
 * @brief Robot::paint Robot visual
 * @param painter Robot visaul
 */
void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(isSelected() ? Qt::red : Qt::white);
    painter->drawEllipse(-size/2,-size/2,size,size);
    // TEMP draw robot direction
    painter->drawLine(QLine(QPoint(0,0), QPoint(0, detectionRange)));
}

void Robot::SetRot(qreal rotation)
{
    rotation = (int)rotation % 360;
    finRotation = rotation;
    setRotation(rotation);
}

// Animate Robots
/**
 * @brief Robot::advance Creates robot behavior
 * @param step signal from timer to move to next frame
 */
void Robot::advance(int step)
{
    finRotation = finRotation%360;
    setRotation(int(rotation()) % 360);

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
            rotationDirection ? setRotation((rotation() - ROTATIONSPEED)) : setRotation((rotation() + ROTATIONSPEED));
        }

        else
        {
            if (dangerObstacle.size() != 0)
            {
                rotationDirection ? finRotation -= rotationAngle: finRotation += rotationAngle;
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
/**
 * @brief Robot::mousePressEvent Selecting robot
 * @param event Mouse click
 */
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
/**
 * @brief Robot::keyPressEvent Controlling selected robot with keyboard
 * @param event Keyboard press
 */
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
