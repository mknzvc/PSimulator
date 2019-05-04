QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

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
    Configuration/iconfiguration.cpp \
    Configuration/inifileconfiguration.cpp \
    LFSR/ilinearfeedbackshiftregister.cpp \
    LFSR/linearfeedbackshiftregister.cpp \
    Utils/ps_utils.cpp \
    Signal/isignalmodel.cpp \
    Signal/sawtoothsignal.cpp \
    Logger/csvwritter.cpp \
    Logger/iwritter.cpp \
    Signal/baseperiodicsignal.cpp \
    SamplerManager/isamplemanager.cpp \
    SamplerManager/samplermanager.cpp \
    Signal/jittersignal.cpp \
    Test/sawsignaltest.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    configuration.ini

HEADERS += \
    Configuration/iconfiguration.h \
    Configuration/inifileconfiguration.h \
    LFSR/ilinearfeedbackshiftregister.h \
    LFSR/linearfeedbackshiftregister.h \
    Utils/ps_utils.h \
    Signal/isignalmodel.h \
    Signal/sawtoothsignal.h \
    Logger/iwritter.h \
    Logger/csvwritter.h \
    Signal/baseperiodicsignal.h \
    SamplerManager/isamplemanager.h \
    SamplerManager/samplermanager.h \
    Signal/jittersignal.h \
    Test/sawsignaltest.h

test{
    message(Configuring test build...)

    TEMPLATE = app
    TARGET = PSimulatorTests

    QT += testlib

    HEADERS += \
        Test/LFSRTest.h

    SOURCES += \
        Test/LFSRTest.cpp

    SOURCES -= main.cpp
}
else{

    TEMPLATE = app
    TARGET = PSimulator

}

INCLUDEPATH += \
    Configuration \
    Utils \
    LFSR \
    Signal \
    Logger \
    SamplerManager
