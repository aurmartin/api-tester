QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Application.cpp \
    Collection.cpp \
    HtmlHighlighter.cpp \
    Request.cpp \
    RequestTabWidget.cpp \
    RequestWidget.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    Application.h \
    Collection.h \
    HtmlHighlighter.h \
    MainWindow.h \
    Request.h \
    RequestTabWidget.h \
    RequestWidget.h

FORMS += \
    MainWindow.ui \
    RequestTabWidget.ui \
    RequestWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
