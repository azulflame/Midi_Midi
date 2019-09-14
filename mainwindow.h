#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QBuffer>

#define SPD_SAMPLE_RATE     8000
#define SPD_FREQ_CONST      ((2.0 * M_PI) / (qreal)SPD_SAMPLE_RATE)
#define SPD_SAMPLE_SIZE     8
#define SPD_CODEC           "audio/pcm"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QBuffer* input;
    QAudioOutput* audio;
    quint16 bpm;
    quint16 beats;

public slots: // this basically means private functions in QT
    QByteArray* makeTone(QByteArray* buffer);
    void playSound();

};

#endif // MAINWINDOW_H
