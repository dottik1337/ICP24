#include <QApplication>
#include "mainwindow.h"

/**
 * @brief main Runs the app
 * @param argc number of arguments
 * @param argv arguments
 * @return return code
 */
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
