#include "Application.h"

#include <QSettings>
#include <QDir>

Application::Application(int &argc, char **argv) :
    QApplication(argc, argv) ,
    mSettings(QSettings::IniFormat,
              QSettings::UserScope,
              QApplication::organizationName(),
              QApplication::applicationName())
{
    initSettings();
}

Application *Application::instance()
{
    return (Application *) QCoreApplication::instance();
}

QSettings &Application::settings()
{
    return instance()->mSettings;
}

void Application::initSettings()
{
    if (mSettings.allKeys().length() != 0) {
        return;
    }

    QDir dir(QFileInfo(mSettings.fileName()).absoluteDir());
    dir.mkdir("collections");
    dir.cd("collections");
    mSettings.setValue("collectionsPath", dir.path());
}
