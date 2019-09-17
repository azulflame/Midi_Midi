#include "mainwindow.h"
#include "ui_mainwindow.h"

#define SAMPLE_RATE 44100.0f
#define TG_MAX_VAL 126
#define FREQ_CONST ((2.0 * M_PI) / SAMPLE_RATE)

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

void MainWindow::on_pushButton_pressed()
{
    //----------------------------Generate the tone---------------------------
    float seconds =1.0f; // how long we want to play our tone
    float freq = 440.0f; // what freq we want to play our tone this is key A4

    QByteArray* bytebuf = new QByteArray();
    bytebuf->resize(seconds * SAMPLE_RATE);
    // sin(2 * pi * frequency * i / sample_rate) will give you a sin tone of the desired frequency, i being an offset

    for (int i=0; i<(seconds * SAMPLE_RATE); i++) {
        double freqOffset = (double)(freq * i); // frequency *i
        freqOffset = freqOffset * FREQ_CONST; // (frequency *i)*((2.0 * M_PI) / SAMPLE_RATE)
        freqOffset = qSin(freqOffset); // sin((frequency *i)*((2.0 * M_PI) / SAMPLE_RATE))
        freqOffset *= TG_MAX_VAL; // now we normalize freqOffset
        (*bytebuf)[i] = (quint8)freqOffset; // stuff that tone into the a byte array, one byte at a time
    }
    //--------------------------------Generate the tone-------------------


    //--------------------------------Play a sound -----------------------
    QAudioFormat format;
    // Set up the format, so that QT knows how to play our tones on our machine
    format.setSampleRate(SAMPLE_RATE);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);


    // Make a QBuffer from our QByteArray
    QBuffer* input = new QBuffer(bytebuf);
    input->open(QIODevice::ReadOnly);

    // Create an output with our premade QAudioFormat (See example in QAudioOutput)
    QAudioOutput* audio = new QAudioOutput(format);
    audio->start(input);

    //this is standerd setup for playing sound in QT, ripped of QT website

    //-------------------------------Play a sound ----------------------------
}
