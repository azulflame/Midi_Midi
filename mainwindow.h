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
#include "note.h"
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
    int main_timer;
    bool isPlaying = false; //Whether or not playback is currently active.
    Song current_song;
    QTimer *q_timer = nullptr;
    //getTones();
    //play C Major
    tone* Tone = toneGenerator.MakeTone(C4,1.0f,0.3); // C4

    tone* Tone1 = toneGenerator.MakeTone(E4,1.0f,0.3);// E4

    tone* Tone2 = toneGenerator.MakeTone(G4,1.0f,0.3); //G4

    tone* Tone3 = toneGenerator.MakeTone(C5,1.0f,0.3); //C5


private slots:
    void on_pushButton_pressed(); //Temporary play button
    void play_song();
    void on_pushButton_2_clicked(); //Temporary pause button

private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
