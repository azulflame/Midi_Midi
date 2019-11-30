#ifndef NADDER_H
#define NADDER_H

#include <QDialog>
#include "pianoroll.h"

namespace Ui {
class NAdder;
}

class NAdder : public QDialog
{
    Q_OBJECT

public:
    explicit NAdder(QWidget *parent = nullptr,
                    PianoRollStaff *block = nullptr);
    ~NAdder();

private slots:
    void on_Reject_clicked();
    void on_sixteenth_clicked(){noteBlock = 1; CheckAccept();}
    void on_eigth_clicked(){noteBlock = 2; CheckAccept();}
    void on_quarter_clicked(){noteBlock = 4; CheckAccept();}
    void on_half_clicked(){noteBlock = 8; CheckAccept();}
    void on_whole_clicked(){noteBlock = 16; CheckAccept();}

    void on_spinBox_valueChanged(int arg1);

    void on_Accept_clicked();

    void on_Merge_clicked();

private:
    Ui::NAdder *ui;
    int noteSize = 0;
        int noteBlock = 0;
        int lastBlock = 0;
        int numNotes = 0;
        int tmpSize;

        bool sizeSelect = false;
        bool validNum = false;

        QString noteNames;

        PianoRollStaff* myBlock;
        void CheckAccept();
        QList<QString> listofNotes;
};

#endif // NADDER_H
