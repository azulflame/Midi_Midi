#ifndef MADDER_H
#define MADDER_H

#include <QDialog>
#include "pianoroll.h"

namespace Ui {
class MAdder;
}

class MAdder : public QDialog
{
    Q_OBJECT

public:
    explicit MAdder(QWidget *parent = nullptr);
    ~MAdder();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_buttonBox_accepted();

private:
    Ui::MAdder *ui;
    int numMeasures;
};

#endif // MADDER_H
