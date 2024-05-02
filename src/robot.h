/**
 * @file robot.h
 * @author Zdeněk Šťastný (xstast41@stud.fit.vutbr.cz)
 * @author Jozef Gallo (xgallo06@stud.fit.vutbr.cz)
 * @brief Header file for Robot class
 * @version 0.1
 * @date 2024-05-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

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
    int rotationAngle = 45; // degrees
    qreal detectionRange = 50;
    qreal speed = 1;
    qreal size = 20;
    void SetRot(qreal rotation);

protected:
    void advance(int step) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;


private:
    int state = 0; // 0 = idle, 1 = forward, 2 = right, 3 = left
    int finRotation = this->rotation();
};


#endif
