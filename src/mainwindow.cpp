#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    auto *sceen = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(sceen);
}

MainWindow::~MainWindow()
{
    delete ui;
}
