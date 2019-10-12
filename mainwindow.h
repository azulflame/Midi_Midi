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



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    float freq = 440.0f;
    double volume = 0.3;
    float seconds = 1.0f;
    ToneGen toneGenerator;
    void start(QIODevice *device);
    QIODevice *device;
    int main_timer;
    bool isPlaying = false;
    std::vector<Note> notes;
    QTimer *q_timer = nullptr;
    //getTones();
    //play C Major
    tone* Tone = toneGenerator.MakeTone(261.63f,1.0f,0.3f); // C4

    tone* Tone1 = toneGenerator.MakeTone(329.63f,1.0f,0.3f);// E4

    tone* Tone2 = toneGenerator.MakeTone(392.0f,1.0f,0.3f); //G4

    tone* Tone3 = toneGenerator.MakeTone(523.251f,1.0f,0.3f); //C5

    QTime *globalTime;

private slots:
    void on_pushButton_pressed();
    void play_song();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
