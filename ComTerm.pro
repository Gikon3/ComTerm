QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CloseEventFilter.cpp \
    ComDataForm.cpp \
    TabForm.cpp \
    main.cpp \
    ComTerm.cpp

HEADERS += \
    CloseEventFilter.h \
    ComDataForm.h \
    ComTerm.h \
    TabForm.h

FORMS += \
    ComDataForm.ui \
    ComTerm.ui \
    TabForm.ui

TRANSLATIONS += \
    ComTerm_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

RC_ICONS += \
    img/icon.ico
