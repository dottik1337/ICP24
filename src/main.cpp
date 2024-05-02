/**
 * @file main.cpp
 * @author Zdeněk Šťastný (xstast41@stud.fit.vutbr.cz)
 * @author Jozef Gallo (xgallo06@stud.fit.vutbr.cz)
 * @brief main function for robot simulation
 * @version 0.1
 * @date 2024-05-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

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
