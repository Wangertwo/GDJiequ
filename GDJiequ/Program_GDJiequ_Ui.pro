QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gdanimationshow.cpp \
    gdcombodelegate.cpp \
    gdconfirmwizardpage.cpp \
    gdherodatabase.cpp \
    gdlogindialog.cpp \
    gdopenprojectthread.cpp \
    gdopenprojectwizard.cpp \
    gdpictureshowbutton.cpp \
    gdpictureshowdialog.cpp \
    gdpicturestatebutton.cpp \
    gdplannerdatabase.cpp \
    gdprelistwidget.cpp \
    gdprelistwidgetitem.cpp \
    gdprojectsetwizardpage.cpp \
    gdprojecttree.cpp \
    gdprojecttreethread.cpp \
    gdprojecttreewidget.cpp \
    gdprojecttreewidgetitem.cpp \
    gdreadonlydelegate.cpp \
    gdregisterdialog.cpp \
    gdremoveprojectdialog.cpp \
    gdslideshowdialog.cpp \
    gduserclient.cpp \
    gdweapondatabase.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    const.h \
    gdanimationshow.h \
    gdcombodelegate.h \
    gdconfirmwizardpage.h \
    gdherodatabase.h \
    gdlogindialog.h \
    gdopenprojectthread.h \
    gdopenprojectwizard.h \
    gdpictureshowbutton.h \
    gdpictureshowdialog.h \
    gdpicturestatebutton.h \
    gdplannerdatabase.h \
    gdprelistwidget.h \
    gdprelistwidgetitem.h \
    gdprojectsetwizardpage.h \
    gdprojecttree.h \
    gdprojecttreethread.h \
    gdprojecttreewidget.h \
    gdprojecttreewidgetitem.h \
    gdreadonlydelegate.h \
    gdregisterdialog.h \
    gdremoveprojectdialog.h \
    gdslideshowdialog.h \
    gduserclient.h \
    gdweapondatabase.h \
    mainwindow.h

FORMS += \
    gdconfirmwizardpage.ui \
    gdherodatabase.ui \
    gdlogindialog.ui \
    gdopenprojectwizard.ui \
    gdpictureshowdialog.ui \
    gdplannerdatabase.ui \
    gdprojectsetwizardpage.ui \
    gdprojecttree.ui \
    gdregisterdialog.ui \
    gdremoveprojectdialog.ui \
    gdslideshowdialog.ui \
    gduserclient.ui \
    gdweapondatabase.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

QT += sql

