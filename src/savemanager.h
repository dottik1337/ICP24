/**
 * @file savemanager.h
 * @author Zdeněk Šťastný (xstast41@stud.fit.vutbr.cz)
 * @author Jozef Gallo (xgallo06@stud.fit.vutbr.cz)
 * @brief Header file for SaveManager class. This class is used for saving and loading scenes from JSON files.
 * @version 0.1
 * @date 2024-05-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QString>
#include <QGraphicsScene>
#include <QJsonObject>
#include "robot.h"
#include "obstacle.h"

class SaveManager
{
private:
    static void AddRobotToScene(QGraphicsScene* scene, qreal x, qreal y, bool rot_dir,
                         qreal rot_angle, qreal det_range, qreal rotation, qreal speed, qreal size);
    static void AddObstacleToScene(QGraphicsScene* scene, qreal x, qreal y, qreal size);

    static QJsonObject makeRobotJson(const Robot *robot);
    static QJsonObject makeObstacleJson(const Obstacle *obstacle);
public:
    static void readJson(QString path, QGraphicsScene* scene);
    static void saveJson(QString path, QGraphicsScene* scene);
};

#endif // SAVEMANAGER_H
