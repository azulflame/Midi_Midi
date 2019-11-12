#include "madder.h"
#include "ui_madder.h"
#include <QDebug>

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
    for(int i = 0; i < numMeasures; i++)
        PianoRollStaff::AddMeasures();

}
