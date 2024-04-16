#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "robot.h"
#include "obstacle.h"
#include <qmath.h>

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
                         ::cos((i * 6.28) / RobotCount) * 400);
        scene->addItem(obstacle);
    }


    QGraphicsRectItem *boundry = new QGraphicsRectItem(scene->sceneRect());
    boundry->setPen(QPen(Qt::red));
    scene->addItem(boundry);


    QGraphicsView view(scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "ICP"));
    view.show();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer->start(1000 / 33);
}
