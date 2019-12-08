#include "nadder.h"
#include "ui_nadder.h"
#include <QMessageBox>
#include <QAction>

NAdder::NAdder(QWidget *parent, PianoRollStaff *block) :
    QDialog(parent),
    ui(new Ui::NAdder)
{
    ui->setupUi(this);
    ui->Accept->setEnabled(false);
    ui->Accept->setStyleSheet("background-color: rgb(225, 225, 225); color: rgb(0, 0, 0);");
    ui->Merge->setEnabled(false);
    ui->Merge->setStyleSheet("background-color: rgb(225, 225, 225); color: rgb(0, 0, 0);");
    ui->MergeNotes->setVisible(false);

    if(block == nullptr) myBlock = nullptr;
    else myBlock = block;
}

NAdder::~NAdder()
{
    delete ui;
}

void NAdder::CheckAccept(){
    if(noteBlock != 0 && numNotes != 0){
        ui->Accept->setEnabled(true);
        ui->Accept->setStyleSheet("background-color: rgb(120, 0, 0); color: rgb(225, 225, 225);");
        ui->Merge->setEnabled(true);
        ui->Merge->setStyleSheet("background-color: rgb(120, 0, 0); color: rgb(225, 225, 225);");
    }else{
        ui->Accept->setEnabled(false);
        ui->Accept->setStyleSheet("background-color: rgb(225, 225, 225); color: rgb(0, 0, 0);");
        ui->Merge->setEnabled(false);
        ui->Merge->setStyleSheet("background-color: rgb(225, 225, 225); color: rgb(0, 0, 0);");
    }
}

void NAdder::on_Reject_clicked()
{
    this->reject();
}

void NAdder::on_spinBox_valueChanged(int arg1)
{
    numNotes = arg1;
    CheckAccept();
}

void NAdder::on_Accept_clicked()
{
    noteSize = noteSize+(numNotes*noteBlock);
    PianoRollStaff::noteLength = noteSize;

    if(myBlock != nullptr) myBlock->AddNote();

    this->accept();
}

void NAdder::on_Merge_clicked()
{
    noteSize = noteSize+(numNotes*noteBlock);
    listofNotes.clear();
    ui->MergeNotes->setVisible(true);
    tmpSize = noteSize;
    QString mergeText;

    if(tmpSize/16 > 0){
        mergeText = QString::number(tmpSize/16);
        listofNotes.push_back(mergeText+" Whole note(s)");
        if(tmpSize%16 != 0) tmpSize = tmpSize%16;
        else tmpSize = 0;
    }
    if(tmpSize/8 > 0){
        mergeText = QString::number(tmpSize/8);
        listofNotes.push_back(mergeText+" Half note(s)");
        if(tmpSize%8 != 0) tmpSize = tmpSize%8;
        else tmpSize = 0;
    }
    if(tmpSize/4 > 0){
        mergeText = QString::number(tmpSize/4);
        listofNotes.push_back(mergeText+" Quarter note(s)");
        if(tmpSize%4 != 0) tmpSize = tmpSize%4;
        else tmpSize = 0;
    }
    if(tmpSize/2 > 0){
        mergeText = QString::number(tmpSize/2);
        listofNotes.push_back(mergeText+" 8th note(s)");
        if(tmpSize%2 != 0) tmpSize = tmpSize%2;
        else tmpSize = 0;
    }
    if(tmpSize/1 > 0){
        mergeText = QString::number(tmpSize/1);
        listofNotes.push_back(mergeText+" 16th note(s)");
        if(tmpSize%1 != 0) tmpSize = tmpSize%1;
        else tmpSize = 0;
    }

    noteBlock = 0;
    if(ui->whole->isChecked()){
        ui->whole->setAutoExclusive(false);
        ui->whole->setChecked(false);
        ui->whole->setAutoExclusive(true);
    }
    else if(ui->half->isChecked()){
        ui->half->setAutoExclusive(false);
        ui->half->setChecked(false);
        ui->half->setAutoExclusive(true);
    }
    else if(ui->quarter->isChecked()){
        ui->quarter->setAutoExclusive(false);
        ui->quarter->setChecked(false);
        ui->quarter->setAutoExclusive(true);
    }
    else if(ui->eigth->isChecked()){
        ui->eigth->setAutoExclusive(false);
        ui->eigth->setChecked(false);
        ui->eigth->setAutoExclusive(true);
    }
    else if(ui->sixteenth->isChecked()){
        ui->sixteenth->setAutoExclusive(false);
        ui->sixteenth->setChecked(false);
        ui->sixteenth->setAutoExclusive(true);
    }
    ui->spinBox->setValue(0);

    mergeText = "";
    for(int i = 0; i < listofNotes.size(); i++)
        mergeText = mergeText+listofNotes[i]+"\n";

    ui->MergeNotes->setText(mergeText);
}
