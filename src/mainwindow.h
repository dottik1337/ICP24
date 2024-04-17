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
    void on_pause_toggled(bool checked);

    void on_GO_clicked();

    void on_LEFT_clicked();

    void on_RIGHT_clicked();

    void on_STOP_clicked();

private:
    Ui::MainWindow *ui;
    void setupScene();
    QGraphicsScene *scene;
};
#endif // MAINWINDOW_H
