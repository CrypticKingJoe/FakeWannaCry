#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);

    App.setApplicationName("WannaCry");
    App.setOrganizationName("iVanilla");
    App.setApplicationVersion("1.0");

    MainWindow Window;
    Window.show();

    return App.exec();
}
