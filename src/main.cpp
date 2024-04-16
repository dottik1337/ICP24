#include <QtMath>
#include <QtWidgets>

#include "robot.h"

static constexpr int RobotCount = 20;


int main(int argc, char **argv)
{
    QApplication app(argc, argv);



    QGraphicsScene scene;
    scene.setSceneRect(-300, -300, 600, 600);

    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    for (int i = 0; i < RobotCount; ++i) {
        Robot *robot = new Robot;
        robot->setPos(::sin((i * 6.28) / RobotCount) * 200,
                      ::cos((i * 6.28) / RobotCount) * 200);
        robot->rotationDirection = i%2;
        scene.addItem(robot);
    }

    QGraphicsRectItem *leftwall = new QGraphicsRectItem();
    leftwall->setRect(-600, -600, 50, 1200);
    leftwall->setBrush(Qt::blue);
    scene.addItem(leftwall);

    QGraphicsRectItem *rightwall = new QGraphicsRectItem();
    rightwall->setRect(600, -600, 50, 1200);
    rightwall->setBrush(Qt::blue);
    scene.addItem(rightwall);

    QGraphicsRectItem *topwall = new QGraphicsRectItem();
    topwall->setRect(-600, -500, 1200, 50);
    topwall->setBrush(Qt::blue);
    scene.addItem(topwall);

    QGraphicsRectItem *botwall = new QGraphicsRectItem();
    botwall->setRect(-600, 450, 1200, 50);
    botwall->setBrush(Qt::blue);
    scene.addItem(botwall);

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    // view.setBackgroundBrush(QPixmap(":/images/cheese.jpg"));

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "ICP"));
    view.resize(400, 300);
    view.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 33);

    return app.exec();
}
