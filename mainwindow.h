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
#include "tonegen.h"



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

private slots:
    void on_pushButton_pressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
