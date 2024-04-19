#include "mainwindow.h"
#include "qevent.h"
#include "ui_mainwindow.h"

#include "robot.h"
#include "obstacle.h"
#include <qmath.h>
#include <QMessageBox> //remove

static constexpr int RobotCount = 20;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupScene();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupScene()
{
    auto *scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    for (int i = 0; i < RobotCount; ++i) {
        Robot *robot = new Robot;
        robot->setPos(::sin((i * 6.28) / RobotCount) * 200,
                      ::cos((i * 6.28) / RobotCount) * 200);
        robot->rotationDirection = i%2;
        scene->addItem(robot);

        Obstacle *obstacle = new Obstacle;
        obstacle->setPos(::sin((i * 6.28) / RobotCount) * 400,
                         ::cos((i * 6.28) / RobotCount) * 80);
        scene->addItem(obstacle);
    }

    scene->addItem(new QGraphicsLineItem(QLineF(scene->sceneRect().topLeft(), scene->sceneRect().topRight())));
    scene->addItem(new QGraphicsLineItem(QLineF(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft())));
    scene->addItem(new QGraphicsLineItem(QLineF(scene->sceneRect().bottomRight(), scene->sceneRect().topRight())));
    scene->addItem(new QGraphicsLineItem(QLineF(scene->sceneRect().bottomRight(), scene->sceneRect().bottomLeft())));

    QGraphicsView view(scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "ICP"));
    view.show();

    this->findChild<QWidget *>("creator")->setVisible(false);
    this->findChild<QWidget *>("creator")->setEnabled(false);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer->start(30);
}


void MainWindow::on_pause_clicked()
{
    if(timer->isActive())
    {
        timer->stop();
    }
    else
    {
        timer->start(30);
    }
}

void MainWindow::on_GO_clicked()
{
    ui->graphicsView->setFocus();
    ui->graphicsView->scene()->setFocus();

    QKeyEvent *simKey = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_W, Qt::NoModifier);
    QApplication::sendEvent(ui->graphicsView->scene(), simKey);
}


void MainWindow::on_LEFT_clicked()
{
    ui->graphicsView->setFocus();
    ui->graphicsView->scene()->setFocus();

    QKeyEvent *simKey = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_A, Qt::NoModifier);
    QApplication::sendEvent(ui->graphicsView->scene(), simKey);
}


void MainWindow::on_RIGHT_clicked()
{
    ui->graphicsView->setFocus();
    ui->graphicsView->scene()->setFocus();

    QKeyEvent *simKey = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_D, Qt::NoModifier);
    QApplication::sendEvent(ui->graphicsView->scene(), simKey);
}


void MainWindow::on_STOP_clicked()
{
    ui->graphicsView->setFocus();
    ui->graphicsView->scene()->setFocus();

    QKeyEvent *simKey = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_S, Qt::NoModifier);
    QApplication::sendEvent(ui->graphicsView->scene(), simKey);
}


void MainWindow::on_actionSIm_triggered()
{
    this->findChild<QWidget *>("controls")->setVisible(true);
    this->findChild<QWidget *>("controls")->setEnabled(true);
    this->findChild<QWidget *>("creator")->setVisible(false);
    this->findChild<QWidget *>("creator")->setEnabled(false);
}


void MainWindow::on_actionCreator_triggered()
{
    timer->stop();
    this->findChild<QWidget *>("controls")->setVisible(false);
    this->findChild<QWidget *>("controls")->setEnabled(false);
    this->findChild<QWidget *>("creator")->setVisible(true);
    this->findChild<QWidget *>("creator")->setEnabled(true);
}



void MainWindow::on_clearScene_clicked()
{
    ui->graphicsView->scene()->clear();
}

