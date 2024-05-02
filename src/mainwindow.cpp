/**
 * @file mainwindow.cpp
 * @author Zdeněk Šťastný (xstast41@stud.fit.vutbr.cz)
 * @author Jozef Gallo (xgallo06@stud.fit.vutbr.cz)
 * @brief Implementation of MainWindow class
 * @version 0.1
 * @date 2024-05-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "mainwindow.h"
#include "qevent.h"
#include "ui_mainwindow.h"

#include "robot.h"
#include "obstacle.h"
#include "savemanager.h"
#include <qmath.h>
#include <QFileDialog>

#define SIM_SPEED 20

static constexpr int RobotCount = 20; //temp remove

/**
 * @brief MainWindow::MainWindow creates ui and scene
 * @param parent parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupScene();
}

/**
 * @brief MainWindow::~MainWindow destroys main window
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::setupScene Sets up scene and timer
 */
void MainWindow::setupScene()
{
    // Set up scene
    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setFixedSize(800,600);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0,0,800,600);

    ui->graphicsView->viewport()->installEventFilter(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    // Spawning testing robots and obstacles
    for (int i = 0; i < RobotCount; ++i) {
        Robot *robot = new Robot;
        robot->setPos(::sin((i * 6.28) / RobotCount) * 200 + 400,
                      ::cos((i * 6.28) / RobotCount) * 200 + 300);
        robot->rotationDirection = i%2;
        robot->SetRot((i%4) * 90);
        scene->addItem(robot);

        Obstacle *obstacle = new Obstacle;
        obstacle->setPos(::sin((i * 6.28) / RobotCount) * 300 + 400,
                         ::cos((i * 6.28) / RobotCount) * 220 + 300);
        scene->addItem(obstacle);
    }

    // Spawning border around items
    scene->addItem(new QGraphicsLineItem(QLineF(scene->sceneRect().topLeft(), scene->sceneRect().topRight())));
    scene->addItem(new QGraphicsLineItem(QLineF(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft())));
    scene->addItem(new QGraphicsLineItem(QLineF(scene->sceneRect().bottomRight(), scene->sceneRect().topRight())));
    scene->addItem(new QGraphicsLineItem(QLineF(scene->sceneRect().bottomRight(), scene->sceneRect().bottomLeft())));

    // Set up window
    QGraphicsView view(scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "ICP"));
    view.show();

    // Default view on Sim
    this->findChild<QWidget *>("creator")->setVisible(false);
    this->findChild<QWidget *>("creator")->setEnabled(false);

    // Set up simulation
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
}


/**
 * @brief MainWindow::eventFilter Filters events and processes them
 * @param obj object to catch events on
 * @param event caught event
 * @return true if event was proccesed
 */
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    // Handeling mouse presses
    if (obj == ui->graphicsView->viewport() && event->type() == QEvent::MouseButtonPress) {

        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        // Adding obstacles
        if (ui->addObstacle->isChecked() && mouseEvent->button() == Qt::LeftButton)
        {
            spawnObstacle(mouseEvent);
            return true;
        }
        // Deleting items
        else if (ui->deleteItem->isChecked() && mouseEvent->button() == Qt::LeftButton)
        {
            removeItem(mouseEvent);
            return true;
        }
        // Adding robots
        else if (ui->addRobot->isChecked() && mouseEvent->button() == Qt::LeftButton)
        {
            spawnRobot(mouseEvent);
            return true;
        }
    }
    // Return event if it isn't filtered
    return QMainWindow::eventFilter(obj, event);
}

// pause simalation
/**
 * @brief MainWindow::on_pause_clicked pauses animation
 */
void MainWindow::on_pause_clicked()
{
    if(timer->isActive())
    {
        timer->stop();
    }
    else
    {
        timer->start(SIM_SPEED);
    }
}

// move manual control robot foreward
/**
 * @brief MainWindow::on_GO_clicked controls manual robot
 */
void MainWindow::on_GO_clicked()
{
    ui->graphicsView->setFocus();
    ui->graphicsView->scene()->setFocus();

    QKeyEvent *simKey = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_W, Qt::NoModifier);
    QApplication::sendEvent(ui->graphicsView->scene(), simKey);
}

// rotate manual control robot left
/**
 * @brief MainWindow::on_GO_clicked controls manual robot
 */
void MainWindow::on_LEFT_clicked()
{
    ui->graphicsView->setFocus();
    ui->graphicsView->scene()->setFocus();

    QKeyEvent *simKey = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_A, Qt::NoModifier);
    QApplication::sendEvent(ui->graphicsView->scene(), simKey);
}

// rotate manual control robot right
/**
 * @brief MainWindow::on_GO_clicked controls manual robot
 */
void MainWindow::on_RIGHT_clicked()
{
    ui->graphicsView->setFocus();
    ui->graphicsView->scene()->setFocus();

    QKeyEvent *simKey = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_D, Qt::NoModifier);
    QApplication::sendEvent(ui->graphicsView->scene(), simKey);
}

// stop manual control robot
/**
 * @brief MainWindow::on_GO_clicked controls manual robot
 */
void MainWindow::on_STOP_clicked()
{
    ui->graphicsView->setFocus();
    ui->graphicsView->scene()->setFocus();

    QKeyEvent *simKey = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_S, Qt::NoModifier);
    QApplication::sendEvent(ui->graphicsView->scene(), simKey);
}

// Switch to SIMULATION mode
/**
 * @brief MainWindow::on_actionSIm_triggered switches to Simulation window
 */
void MainWindow::on_actionSIm_triggered()
{
    ui->controls->setVisible(true);
    ui->controls->setEnabled(true);
    ui->creator->setVisible(false);
    ui->creator->setEnabled(false);

    ui->addObstacle->setChecked(false);
    ui->addRobot->setChecked(false);
    ui->deleteItem->setChecked(false);
}

// Switch to CREATOR mode
/**
 * @brief MainWindow::on_actionCreator_triggered switches to Creator window
 */
void MainWindow::on_actionCreator_triggered()
{
    timer->stop();

    ui->controls->setVisible(false);
    ui->controls->setEnabled(false);
    ui->creator->setVisible(true);
    ui->creator->setEnabled(true);
}

// Remove all items from scene
/**
 * @brief MainWindow::on_clearScene_clicked Clears scene
 */
void MainWindow::on_clearScene_clicked()
{
    this->clearScene();
}

// Spawn obstacle on cursor position when left-click
/**
 * @brief MainWindow::spawnObstacle Spawns Obstacles on mouse click
 * @param event mouse click
 */
void MainWindow::spawnObstacle(QMouseEvent *event)
{
    Obstacle *obstacle = new Obstacle();
    obstacle->size = ui->crObstacleSize->value();
    obstacle->setPos(ui->graphicsView->mapToScene(event->pos()));
    ui->graphicsView->scene()->addItem(obstacle);
}

// Remove item on cursor position when left-click
/**
 * @brief MainWindow::removeItem Deletes item on mouse click
 * @param event mouse click
 */
void MainWindow::removeItem(QMouseEvent *event)
{
    QGraphicsItem *item = ui->graphicsView->scene()->itemAt(ui->graphicsView->mapToScene(event->pos()), QTransform());
    ui->graphicsView->scene()->removeItem(item);
}

// Spawn robot on cursor position when left-click
/**
 * @brief MainWindow::spawnRobot Spawns robot on mouse click
 * @param event mouse click
 */
void MainWindow::spawnRobot(QMouseEvent *event)
{
    Robot *robot = new Robot();
    robot->size = ui->crRobotSize->value();
    robot->detectionRange = ui->crRobotDetectionRange->value() > ui->crRobotSize->value()/2 ? ui->crRobotDetectionRange->value() : ui->crRobotSize->value()/2;
    robot->rotationAngle = ui->crRobotRotationAngle->value();
    robot->rotationDirection = ui->crRobotRotationDirection->currentIndex();
    robot->SetRot(ui->crRobotDirection->value());

    robot->setPos(ui->graphicsView->mapToScene(event->pos()));
    ui->graphicsView->scene()->addItem(robot);
}

// Select ADD_ROBOT mode
/**
 * @brief MainWindow::on_addRobot_clicked switches mode
 */
void MainWindow::on_addRobot_clicked()
{
    ui->addObstacle->setChecked(false);
    ui->deleteItem->setChecked(false);
}

// Select ADD_OBSTACLE mode
/**
 * @brief MainWindow::on_addRobot_clicked switches mode
 */
void MainWindow::on_addObstacle_clicked()
{
    ui->addRobot->setChecked(false);
    ui->deleteItem->setChecked(false);
}

// Select DELETE mode
/**
 * @brief MainWindow::on_addRobot_clicked switches mode
 */
void MainWindow::on_deleteItem_clicked()
{
    ui->addRobot->setChecked(false);
    ui->addObstacle->setChecked(false);
}

// Loads file
void MainWindow::on_loadScene_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                "../ICP/examples", // QoL change
                                                tr("JSON file (*.json)"));
    if (path.isEmpty()) return;
    this->clearScene();
    try {
        SaveManager::readJson(path, ui->graphicsView->scene()); // using existing scene instead of creating new one
    }
    catch (std::exception &e){
        qWarning() << e.what();
    }
}


void MainWindow::on_saveScene_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                "../ICP/examples", // QoL change
                                                tr("JSON file (*.json)"));
    if (path.isEmpty()) return;
    try {
        SaveManager::saveJson(path, this->ui->graphicsView->scene());
    }
    catch (std::exception &e){
        qWarning() << e.what();
    }

}

void MainWindow::clearScene(){
    scene->clear();

    // spawning border around scene
    scene->addItem(new QGraphicsLineItem(QLineF(scene->sceneRect().topLeft(), scene->sceneRect().topRight())));
    scene->addItem(new QGraphicsLineItem(QLineF(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft())));
    scene->addItem(new QGraphicsLineItem(QLineF(scene->sceneRect().bottomRight(), scene->sceneRect().topRight())));
    scene->addItem(new QGraphicsLineItem(QLineF(scene->sceneRect().bottomRight(), scene->sceneRect().bottomLeft())));
}

