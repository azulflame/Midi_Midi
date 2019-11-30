#include <QApplication>
#include "common.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // start main window
    //MainWindow w; // this has to be before the ToneGen thread, or we will get a terrible sounding synth

    GlobalMainWindow = new MainWindow;

    ToneGen toneGenerator; // start tonegen
    //toneGenerator.b_IsRealTime = true; // allow for play on keyboard
    toneGenerator.start(); // start the thread

    GlobalMainWindow->setToneGenPtr(&toneGenerator); // set up the global pointer
    GlobalToneGenPntr = &toneGenerator; // set the pnter



    qDebug()  << GlobalToneGenPntr;
    GlobalMainWindow->show();       // show the main window


    return a.exec();
}
