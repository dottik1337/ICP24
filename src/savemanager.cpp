/**
 * @file savemanager.cpp
 * @author Zdeněk Šťastný (xstast41@stud.fit.vutbr.cz)
 * @author Jozef Gallo (xgallo06@stud.fit.vutbr.cz)
 * @brief Impementation of SaveManager class. Class is responsible for saving and loading game state.
 * @version 0.1
 * @date 2024-05-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "savemanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include "exceptions/GameLoadException.h"
#include "exceptions/GameSaveException.h"

/**
 * @brief SaveManager::readJson reads Json file and loads robots and obstacles to the scene
 * @param path Json file path
 * @param scene scene where robots and obstacles should be loaded
 */
void SaveManager::readJson(QString path, QGraphicsScene* scene){
    QString val;
    QFile file;
    QJsonDocument doc;

    // Loading file
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    // Parsing Json
    doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject info = doc.object();
    if(info.isEmpty()){
        throw GameLoadException();
    }

    // Getting robots and obstacles arrays
    QJsonArray robots = info.value(QString("robots")).toArray();
    QJsonArray obstacles = info.value(QString("obstacles")).toArray();

    for (auto it = robots.begin(); it != robots.end();it++){
        QJsonObject robot = it->toObject();
        QJsonValue x = robot["x"];
        QJsonValue y =robot["y"];
        QJsonValue det_range = robot["det_range"];
        QJsonValue rot_dir = robot["rot_dir"];
        QJsonValue speed = robot["speed"];
        QJsonValue rotation = robot["rotation"];
        QJsonValue rot_angle = robot["rot_angle"];
        QJsonValue size = robot["size"];

        // Chceck if Json values are correct
        if (!(x.isDouble() && y.isDouble() && det_range.isDouble() && rot_dir.isBool()
              && speed.isDouble() && rotation.isDouble() && rot_angle.isDouble() && size.isDouble()))
            throw GameLoadException();

        // Adds robot to scene
        AddRobotToScene(scene, x.toDouble(), y.toDouble(), rot_dir.toBool(),
                             rot_angle.toDouble(), det_range.toDouble(),rotation.toDouble(),speed.toDouble(), size.toDouble());

    }

    for (auto it = obstacles.begin(); it != obstacles.end();it++){
        QJsonObject obstacle = it->toObject();
        QJsonValue x = obstacle["x"];
        QJsonValue y =obstacle["y"];
        QJsonValue size = obstacle["size"];

        // Check if Json values are correct
        if (!(x.isDouble() && y.isDouble() && size.isDouble()))
            throw GameLoadException();

        // Adds Obstacle to scene
        AddObstacleToScene(scene, x.toDouble(), y.toDouble(), size.toDouble());
    }
}

/**
 * @brief SaveManager::AddRobotToScene adds robot to scene
 * @param scene to add to
 * @param x parameter of robot
 * @param y parameter of robot
 * @param rot_dir parameter of robot
 * @param rot_angle parameter of robot
 * @param det_range parameter of robot
 * @param rotation parameter of robot
 * @param speed parameter of robot
 */
void SaveManager::AddRobotToScene(QGraphicsScene* scene, qreal x, qreal y, bool rot_dir,
                     qreal rot_angle, qreal det_range, qreal rotation, qreal speed, qreal size){
    Robot *robot = new Robot;

    // Checking if the object is out of scene bounds
    auto width = scene->sceneRect().right();
    auto height = scene->sceneRect().bottom();
    if (x > width || x < 0 || y > height || y < 0)
        throw GameLoadException();

    // Setting parameters
    robot->setPos(x,y);
    robot->rotationDirection = rot_dir;
    robot->rotationAngle = rot_angle;
    robot->detectionRange = det_range;
    robot->speed = speed;
    robot->setRotation(rotation);
    robot->finRotation = rotation;
    robot->size = size;

    scene->addItem(robot);
}

/**
 * @brief SaveManager::AddObstacleToScene adds obstacle to scene
 * @param scene to add to
 * @param x parameter of obstacle
 * @param y parameter of obstacle
 * @param size parameter of obstacle
 */
void SaveManager::AddObstacleToScene(QGraphicsScene* scene, qreal x, qreal y, qreal size){
    Obstacle *obstacle = new Obstacle;

    // Checking if the object is out of scene bounds
    auto width = scene->sceneRect().right();
    auto height = scene->sceneRect().bottom();
    if (x > width || x < 0 || y > height || y < 0)
        throw GameLoadException();

    // Setting parameters
    obstacle->setPos(x,y);
    obstacle->size = size;

    scene->addItem(obstacle);
}

/**
 * @brief SaveManager::saveJson saves current game state to Json file
 * @param path save file path
 * @param scene from which should robots/obstacles be saved
 */
void SaveManager::saveJson(QString path, QGraphicsScene* scene){
    QFile saveFile(path);
    QJsonObject mainObj;
    QJsonArray robots;
    QJsonArray obstacles;

    // Iterate over items in scene
    QList<QGraphicsItem *> items;
    items = scene->items();
    for ( auto item : scene->items() )
    {
        // item is instance of Robot
        if (auto robot = dynamic_cast<const Robot*>(item)){
            auto r = makeRobotJson(robot);
            robots.append(r);
        }
        // item is instance of Obstacle
        else if (auto obstacle = dynamic_cast<const Obstacle*>(item)){
            auto o = makeObstacleJson(obstacle);
            obstacles.append(o);
        }
    }

    // Correctly formatting Json
    mainObj["robots"] = robots;
    mainObj["obstacles"] = obstacles;
    QJsonDocument doc(mainObj);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        throw GameSaveException();
    }

    // Writing to file
    saveFile.write(doc.toJson());
}

/**
 * @brief SaveManager::makeRobotJson turns Robot objects into QJsonObjects
 * @param robot to be turned into QJsonObject
 * @return QJsonObject from Robot object
 */
QJsonObject SaveManager::makeRobotJson(const Robot *robot){
    QJsonObject obj;
    obj["x"] = robot->x();
    obj["y"] = robot->y();
    obj["speed"] = robot->speed;
    obj["rot_angle"] = robot->rotationAngle;
    obj["rot_dir"] = robot->rotationDirection;
    obj["det_range"] = robot->detectionRange;
    obj["rotation"] = robot->rotation();
    obj["size"] = robot->size;
    return obj;
}

/**
 * @brief SaveManager::makeObstacleJson turns Obstacle objects into QJsonObjects
 * @param obstacle to be turned into QJsonObject
 * @return QJsonObject from Obstacle object
 */
QJsonObject SaveManager::makeObstacleJson(const Obstacle *obstacle){
    QJsonObject obj;
    obj["x"] = obstacle->x(); //not working correctly
    obj["y"] = obstacle->y(); //TODO
    obj["size"] = obstacle->size;
    return obj;
}
