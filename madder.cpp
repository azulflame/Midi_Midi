#include "madder.h"
#include "ui_madder.h"
#include <QDebug>

int PianoRollStaff::measureAddition = 0;

MAdder::MAdder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MAdder)
{
    ui->setupUi(this);
}

MAdder::~MAdder()
{
    delete ui;
}

void MAdder::on_spinBox_valueChanged(int arg1)
{
    numMeasures = arg1;
}

void MAdder::on_buttonBox_accepted()
{
    PianoRollStaff::measureAddition = numMeasures;
    qDebug() << numMeasures;
}
