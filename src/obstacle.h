/**
 * @file obstacle.h
 * @author Zdeněk Šťastný (xstast41@stud.fit.vutbr.cz)
 * @author Jozef Gallo (xgallo06@stud.fit.vutbr.cz)
 * @brief Header file for Obstacle class
 * @version 0.1
 * @date 2024-05-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

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
};

#endif // OBSTACLE_H
