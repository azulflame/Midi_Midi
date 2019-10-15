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
