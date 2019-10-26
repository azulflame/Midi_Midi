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
    toneGenerator.start();

    tone tone1;
    tone1.frequcnecy = 64;
    //tone1.bToneOn = true;


    toneGenerator.toneVector.push_back(tone1);


    return a.exec();
}
