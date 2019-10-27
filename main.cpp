#include "mainwindow.h"
#include <QApplication>
#include "tonegen.h"
#include "tone.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ToneGen toneGenerator;
    //ToneGen RealTimePlay;

    //RealTimePlay.b_IsRealTime = true;

    //RealTimePlay.start();
    toneGenerator.start();

    //tone tone1(64);
    //tone1.frequcnecy = 64;
    //tone1.bToneOn = true;
    //tone tone2(10);
   // tone1.frequcnecy = 64;
   //tone2.bToneOn = true;
    //tone tone3(71);
    //tone1.frequcnecy = 64;
    //tone3.bToneOn = true;
    //tone tone4(60);
    //tone1.frequcnecy = 64;
    //tone4.bToneOn = true;


    //toneGenerator.toneVector.push_back(&tone1);
    //toneGenerator.toneVector.push_back(&tone2);
    //toneGenerator.toneVector.push_back(&tone3);
    //toneGenerator.toneVector.push_back(&tone4);


    toneGenerator.b_IsRealTime = false;
    //GlobalToneGenPntr = &toneGenerator;
    MainWindow::setToneGenPtr(&toneGenerator);

    qDebug()  << GlobalToneGenPntr;


    return a.exec();
}
