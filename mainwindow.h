#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtMultimedia>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QBuffer>
#include <QDebug>
#include <QKeyEvent>
#include <QWidget>
#include <QTimer>
#include <vector>
#include "tonegen.h"
#include "tone.h"
#include "midinote.h"
#include "notemap.h"
#include "song.h"

namespace Ui {
class MainWindow;
}

/*
 * The MainWindow class is responsible for the operations of the main application
 * window. We will use this as our "connector" for our individual components to
 * communicate with one another.
 *
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ToneGen toneGenerator;
    void start(QIODevice *device);
    QIODevice *device;
    unsigned long long int main_timer;
    Song current_song;
    bool isPlaying = false; //Whether or not playback is currently active.
    QTimer *q_timer = nullptr;
    vector<MidiNote> delete_queue;
    //getTones();
    //play C Major


    void static setToneGenPtr(ToneGen *CurrentToneGen);

private slots:
    void on_pushButton_pressed(); //Temporary play button
    void play_song();
    void on_pushButton_2_clicked(); //Temporary pause button

    void on_action16th_triggered();

    void on_action8th_triggered();

    void on_actionQuarter_triggered();

    void on_actionHalf_triggered();

    void on_actionWhole_triggered();

    void on_checkBox_stateChanged(int arg1);


private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
