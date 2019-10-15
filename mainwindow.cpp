#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "audioconstants.h"
#include "note.h"
#include <QKeyEvent>
#include <QAudioDeviceInfo>
#include <QIODevice>
#include <QDebug>
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    void start(QIODevice *device);

    globalTime = new QTime();

    globalTime->start();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{
    if(q_timer != nullptr)
    {
        disconnect(q_timer, SIGNAL(timeout()), this, SLOT(play_song()));
    }

    isPlaying = true;
    q_timer = nullptr;
    notes.clear();

    //play C Major
    tone* Tone = toneGenerator.MakeTone(261.63f,1.0f,0.3f); // C4

    tone* Tone1 = toneGenerator.MakeTone(329.63f,1.0f,0.3f);// E4

    tone* Tone2 = toneGenerator.MakeTone(392.0f,1.0f,0.3f); //G4

    tone* Tone3 = toneGenerator.MakeTone(523.251f,1.0f,0.3f); //C5


    Note note;
    note.setNote(Tone, 0);
    Note note1;
    note1.setNote(Tone1, 960);
    Note note2;
    note2.setNote(Tone2, 1920);
    Note note3;
    note3.setNote(Tone3, 2880);
    Note note4;
    note4.setNote(Tone2, 3840);
    Note note5;
    note5.setNote(Tone1, 4800);
    Note note6;
    note6.setNote(Tone, 5760);

    notes.push_back(note);
    notes.push_back(note1);
    notes.push_back(note2);
    notes.push_back(note3);
    notes.push_back(note4);
    notes.push_back(note5);
    notes.push_back(note6);

    q_timer = new QTimer(this);
    connect(q_timer, SIGNAL(timeout()), this, SLOT(play_song()));
    q_timer->start(16);
    main_timer = 0;
}

void MainWindow::play_song()
{
    for (int i=0; i < notes.size(); i++)
    {
        if(main_timer == notes.at(i).start_time)
        {
            toneGenerator.PlayTone(notes.at(i).Tone);
        }
    }

    main_timer += 16;
}

void MainWindow::start(QIODevice *device)
{
        device->open(QIODevice::ReadOnly);

}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Z){
        //tone* Tone = toneGenerator.MakeTone(261.63f,1.0f,0.3f); // C4
        //toneGenerator.PlayTone(Tone);
        //toneGenerator.RealTimePlay(440.0f,0.3f,globalTime->elapsed());
        toneGenerator.toneType++;
        toneGenerator.toneType = (toneGenerator.toneType)%4;
        qDebug() << toneGenerator.toneType;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(isPlaying)
    {
        isPlaying = false;
        q_timer->stop();
    }
    else
    {
        isPlaying = true;
        q_timer->start();
    }


}