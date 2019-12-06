#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "audioconstants.h"
#include "midinote.h"
#include "filemanager.h"
#include "notemap.h"
#include <QKeyEvent>
#include <QAudioDeviceInfo>
#include <QIODevice>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include "pianoroll.h"
#include "common.h"
#include <map>
#include <vector>

typedef std::vector<MidiNote> tone_vector;
int PianoRollStaff::noteLength = 4;
bool PianoRollStaff::PianoInteract;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    void start(QIODevice *device);
    ui->mainToolBar->setStyleSheet("background-color: rgb(120, 0, 0);");
    ui->pushButton->setCheckable(true);

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

    //Clear all current sound
    for(int x = (delete_queue.size() - 1); x >= 0; x--)
    {
        GlobalToneGenPntr->stopTone(delete_queue[x].value);
        delete_queue.erase(delete_queue.begin() + x);
    }

    q_timer = new QTimer(this);
    connect(q_timer, SIGNAL(timeout()), this, SLOT(play_song()));
    q_timer->start(60000 / (16 * TAdder::Tempo));
    main_timer = 0;

    if(isPlaying)
    {
        play_song();
    }
}

void MainWindow::play_song()
{
    std::map<int, tone_vector>::iterator track_iterator;

    //Stop notes
    for(int x = (delete_queue.size() - 1); x >= 0; x--)
    {
        if(main_timer >= delete_queue[x].duration)
        {
            GlobalToneGenPntr->stopTone(delete_queue[x].value);
            delete_queue.erase(delete_queue.begin() + x);
        }
    }

    //Continue playing the song until play has stopped
    for(int i = main_timer; i < (main_timer + 19); i++)
    {
        //Play notes
        track_iterator = current_song.tracks.at(0).note_map.find(i);

        if(track_iterator != current_song.tracks.at(0).note_map.end())
        {
            //Play each note that exists at the current start time
            for(int j = 0; j < current_song.tracks.at(0).note_map[main_timer].size(); j++)
            {
                GlobalToneGenPntr->playTone(current_song.tracks.at(0).note_map[main_timer].at(j).value);
                //Add to delete queue
                MidiNote new_delete;
                new_delete.value = current_song.tracks.at(0).note_map[main_timer].at(j).value;
                new_delete.duration = main_timer + (current_song.tracks.at(0).note_map[main_timer].at(j).duration * 20);
                delete_queue.push_back(new_delete);
            }
        }
    }

    main_timer += 5;
    if(main_timer > last_tick)
    {
        main_timer = 0;
        for(int x = (delete_queue.size() - 1); x >= 0; x--)
        {
            GlobalToneGenPntr->stopTone(delete_queue[x].value);
            delete_queue.erase(delete_queue.begin() + x);
        }
    }
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
        for(int x = (delete_queue.size() - 1); x >= 0; x--)
        {
            GlobalToneGenPntr->stopTone(delete_queue[x].value);
            delete_queue.erase(delete_queue.begin() + x);
        }
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

void MainWindow::on_actionSave_triggered()
{
    file_manager.save_file(current_song);
}

void MainWindow::on_actionLoad_triggered()
{
    file_manager.load_file();
    return;
}
void MainWindow::on_actionImport_triggered()
{
    file_manager.import_file();
    return;
}
void MainWindow::on_actionExport_triggered()
{
    file_manager.export_file();
    return;
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "MIDI_MIDI",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    qDebug()<< GlobalToneGenPntr;
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        GlobalToneGenPntr->killThread = true;
        GlobalToneGenPntr->quit();
        while(GlobalToneGenPntr->isRunning()) // wait for thread to kill itself
        {
            //do nothing
        }
        // then you may close the program
        event->accept();
    }
}

void MainWindow::actionCurrent_Synth_triggered(){


}



void MainWindow::on_relDial_3_sliderMoved(int position)//Release
{
    //gRelease = position ;
    GlobalToneGenPntr->gRelease = position *0.01;
    //qDebug() << GlobalToneGenPntr->gRelease ;
}

void MainWindow::on_atkDial_3_sliderMoved(int position)//Attack
{
    GlobalToneGenPntr->gAttack = position *0.01;
}

void MainWindow::on_susDial_3_sliderMoved(int position)//Sustain
{
    GlobalToneGenPntr->gSustain = position*0.01;
}


void MainWindow::on_decDial_3_sliderMoved(int position)//Decay
{
    GlobalToneGenPntr->gDecay = position *0.01;
}
