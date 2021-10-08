QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    global_variate.cpp \
    class_def/bfile.cpp \
    class_def/user.cpp \
    class_def/usermanager.cpp \
    class_def/vocabulary.cpp \
    class_def/vocabularymanager.cpp \
    class_def/testprocess.cpp \ 
    class_def/vocabularystatistics.cpp \
    forms/mainwindow.cpp \
    forms/loginwindow.cpp \
    forms/registerwindow.cpp \
    forms/testprocesswindow.cpp \
    forms/libmanagewindow.cpp \
    sha1/sha1.cpp

HEADERS += \
    global_variate.h \
    class_def/bfile.h \
    class_def/user.h \
    class_def/usermanager.h \
    class_def/vocabulary.h \
    class_def/vocabularymanager.h \
    class_def/testprocess.h \
    class_def/vocabularystatistics.h \
    forms/mainwindow.h \
    forms/loginwindow.h \
    forms/registerwindow.h \
    forms/testprocesswindow.h \
    forms/libmanagewindow.h \
    sha1/sha1.h

FORMS += \
    forms_ui/testprocesswindow.ui \
    forms_ui/loginwindow.ui \
    forms_ui/mainwindow.ui \
    forms_ui/registerwindow.ui\
    forms_ui/libmanagewindow.ui 

TRANSLATIONS += \
    translations\WordsMemorizing_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
