#include "tadder.h"
#include "ui_tadder.h"
int TAdder::Tempo = 130;

TAdder::TAdder(QWidget *parent, PianoRollStaff *block) :
    QDialog(parent),
    ui(new Ui::TAdder)
{
    ui->setupUi(this);
    myPiano = block;
    ui->spinBox->setRange(1, 999);
}

TAdder::~TAdder()
{
    delete ui;
}

void TAdder::on_spinBox_valueChanged(int arg1)
{
    numTempo = arg1;
}

void TAdder::on_buttonBox_accepted()
{
    Tempo = numTempo;
}
