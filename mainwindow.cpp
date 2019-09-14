

#include "mainwindow.h"
#include "ui_mainwindow.h"


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

void MainWindow::playSound()
{
    QBuffer* input = new QBuffer();
    bpm = 40;
    QByteArray* buf = new QByteArray(9 * 60 * SPD_SAMPLE_RATE / bpm, 0);
    QByteArray* gen = makeTone(buf);
    input->setData(*gen);

    QAudioFormat format;
    format.setSampleRate(SPD_SAMPLE_RATE);
    format.setChannelCount(1);
    format.setSampleSize(SPD_SAMPLE_SIZE);
    format.setCodec(SPD_CODEC);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
       qWarning() << "Raw audio format not supported by backend, cannot play audio.";
       return;
    }

    audio = new QAudioOutput(format, this);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));

    input->open(QIODevice::ReadOnly);
    audio->start(input);
}

QByteArray* MainWindow::makeTone(QByteArray* buffer){

    qreal t;
    qreal freq = 840;
    uint start, end;


    // samples = beats * (min/beat) * (sec/min) * (samples/sec)
    start = ((uint)1) * 60 * SPD_SAMPLE_RATE / (uint)40;
    end = ((uint)5000) * 60 * SPD_SAMPLE_RATE / (uint)40;

    // make sure we have the size
    if ((uint)buffer->size() < end) {
        buffer->resize(end);
    }

    for (uint i=start; i<end; i++) {
        t = freq * (qreal)i;
        t = t * SPD_FREQ_CONST;

        (*buffer)[i] = (qint8)t;
    }
    return buffer;

}


