#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer *timer;

private slots:
    void on_pause_clicked();

    void on_GO_clicked();

    void on_LEFT_clicked();

    void on_RIGHT_clicked();

    void on_STOP_clicked();

    void on_actionSIm_triggered();

    void on_actionCreator_triggered();

    void on_clearScene_clicked();

    void on_addRobot_clicked();

    void on_addObstacle_clicked();

    void on_deleteItem_clicked();

private:
    Ui::MainWindow *ui;
    void setupScene();
    QGraphicsScene *scene;
    bool eventFilter(QObject *obj, QEvent *event);
    void spawnObstacle(QMouseEvent *event);
    void removeItem(QMouseEvent *event);
    void spawnRobot(QMouseEvent *event);
};
#endif // MAINWINDOW_H
