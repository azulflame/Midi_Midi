#-------------------------------------------------
#
# Project created by QtCreator 2019-09-14T17:18:44
#
#-------------------------------------------------


QT       += core gui
QT       += multimedia
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Midi_midi
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Midi_import/Binasc.cpp \
        Midi_import/MidiEvent.cpp \
        Midi_import/MidiEventList.cpp \
        Midi_import/MidiFile.cpp \
        Midi_import/MidiMessage.cpp \
        common.cpp \
        filemanager.cpp \
        madder.cpp \
        main.cpp \
        mainwindow.cpp \
        midinote.cpp \
        nadder.cpp \
        pianoroll.cpp \
        song.cpp \
        tadder.cpp \
        tone.cpp \
        tonegen.cpp \
        track.cpp \
        virtualpiano.cpp

HEADERS += \
        Midi_import/Binasc.h \
        Midi_import/MidiEvent.h \
        Midi_import/MidiEventList.h \
        Midi_import/MidiFile.h \
        Midi_import/MidiMessage.h \
        audioconstants.h \
        common.h \
        filemanager.h \
        madder.h \
        mainwindow.h \
        midinote.h \
        nadder.h \
        notemap.h \
        olcnoisemaker.h \
        pianoroll.h \
        song.h \
        tadder.h \
        tone.h \
        tonegen.h \
        track.h \
        virtualpiano.h

FORMS += \
        madder.ui \
        mainwindow.ui \
        nadder.ui \
        tadder.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32: LIBS += -lWinMM
