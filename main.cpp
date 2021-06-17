#include "MainWindow.h"
#include "Application.h"

#include <iostream>

void customLogHandler(QtMsgType, const QMessageLogContext&,
                      const QString& msg)
{
    std::cout << msg.toStdString() << std::endl;
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(&customLogHandler);

    QApplication::setOrganizationName("aurmartin");
    QApplication::setApplicationName("ApiTester");

    Application a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
