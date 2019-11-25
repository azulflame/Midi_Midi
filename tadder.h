#ifndef TADDER_H
#define TADDER_H

#include <QDialog>
#include "pianoroll.h"

namespace Ui {
class TAdder;
}

class TAdder : public QDialog
{
    Q_OBJECT

public:
    explicit TAdder(QWidget *parent = nullptr,
                    PianoRollStaff *block = nullptr);
    ~TAdder();
    static int Tempo;

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_buttonBox_accepted();

private:
    Ui::TAdder *ui;
    PianoRollStaff *myPiano;
    int numTempo;
};

#endif // TADDER_H
