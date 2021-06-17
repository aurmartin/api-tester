#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QApplication>
#include <QSettings>

class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int &argc, char **argv);

    static Application *instance();
    static QSettings &settings();

private:
    void initSettings();

private:
    QSettings mSettings;
};

#endif // APPLICATION_H
