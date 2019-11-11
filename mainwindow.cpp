#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "audioconstants.h"
#include "note.h"
#include "notemap.h"
#include <QKeyEvent>
#include <QAudioDeviceInfo>
#include <QIODevice>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include "pianoroll.h"

int PianoRollStaff::noteLength;
bool PianoRollStaff::PianoInteract;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    void start(QIODevice *device);



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
/*    notes.clear();

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
*/

    q_timer = new QTimer(this);
    connect(q_timer, SIGNAL(timeout()), this, SLOT(play_song()));
    q_timer->start(16);
    main_timer = 0;
}

void MainWindow::play_song()
{/*
    for (int i=0; i < notes.size(); i++)
    {
        if(main_timer == notes.at(i).start_time)
        {
            toneGenerator.PlayTone(notes.at(i).Tone);
        }
    }
*/
    main_timer += 16;
}

void MainWindow::start(QIODevice *device)
{
        device->open(QIODevice::ReadOnly);

}

void MainWindow::keyPressEvent(QKeyEvent *event){
//FOR TESTING THE SYNTH
//    if(event->key() == Qt::Key_Z){
//       GlobalToneGenPntr->addTone(C4);
//       qDebug()  << GlobalToneGenPntr;
//       GlobalToneGenPntr->playTone(C4);

//    }

//    if(event->key() == Qt::Key_X){
//        GlobalToneGenPntr->addTone(B4);
//        qDebug()  << GlobalToneGenPntr;
//        GlobalToneGenPntr->playTone(B4);

//    }

//    if(event->key() == Qt::Key_C){
//        GlobalToneGenPntr->addTone(A4);
//        qDebug()  << GlobalToneGenPntr;
//        GlobalToneGenPntr->playTone(A4);

//    }
//    if(event->key() == Qt::Key_V){
//        GlobalToneGenPntr->addTone(D4);
//        qDebug()  << GlobalToneGenPntr;
//        GlobalToneGenPntr->playTone(D4);

//    }
//    if(event->key() == Qt::Key_B){
//        GlobalToneGenPntr->addTone(E4);
//        qDebug()  << GlobalToneGenPntr;
//        GlobalToneGenPntr->playTone(E4);

//    }

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

void MainWindow::setToneGenPtr(ToneGen *CurrentToneGen){

    GlobalToneGenPntr = CurrentToneGen;
}


void MainWindow::on_action16th_triggered()
{
    ui->action8th->setChecked(false);
    ui->actionQuarter->setChecked(false);
    ui->actionHalf->setChecked(false);
    ui->actionWhole->setChecked(false);
    PianoRollStaff::noteLength = 1;
}

void MainWindow::on_action8th_triggered()
{
    ui->action16th->setChecked(false);
    ui->actionQuarter->setChecked(false);
    ui->actionHalf->setChecked(false);
    ui->actionWhole->setChecked(false);
    PianoRollStaff::noteLength = 2;
}

void MainWindow::on_actionQuarter_triggered()
{
    ui->action8th->setChecked(false);
    ui->action16th->setChecked(false);
    ui->actionHalf->setChecked(false);
    ui->actionWhole->setChecked(false);
    PianoRollStaff::noteLength = 4;
}

void MainWindow::on_actionHalf_triggered()
{
    ui->action8th->setChecked(false);
    ui->actionQuarter->setChecked(false);
    ui->action16th->setChecked(false);
    ui->actionWhole->setChecked(false);
    PianoRollStaff::noteLength = 8;
}

void MainWindow::on_actionWhole_triggered()
{
    ui->action8th->setChecked(false);
    ui->actionQuarter->setChecked(false);
    ui->actionHalf->setChecked(false);
    ui->action16th->setChecked(false);
    PianoRollStaff::noteLength = 16;
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 2) PianoRollStaff::PianoInteract = true;
    else PianoRollStaff::PianoInteract = false;
}

void MainWindow::on_action_Measures_triggered()
{
    MAdder dialog;
    dialog.setModal(true);
    dialog.exec();
}
