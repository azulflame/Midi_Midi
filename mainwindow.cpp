#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "audioconstants.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{

    //play C Major
    tone* Tone = toneGenerator.MakeTone(261.63f,1.0f,0.3f); // C4

    tone* Tone1 = toneGenerator.MakeTone(329.63f,1.0f,0.3f);// E4

    tone* Tone2 = toneGenerator.MakeTone(392.0f,1.0f,0.3f); //G4

    toneGenerator.PlayTone(Tone);
    toneGenerator.PlayTone(Tone1);
    toneGenerator.PlayTone(Tone2);


}
