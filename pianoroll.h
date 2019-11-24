#ifndef PIANOROLL_H
#define PIANOROLL_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QPaintEvent>
#include <QList>
#include <QMap>
#include <QColor>
#include <QReadWriteLock>
#include <QDebug>
#include <vector>
#include "tonegen.h"

namespace Ui {
class PianoRoll;
}

class PianoRollStaff : public QObject, QGraphicsRectItem
{
    Q_OBJECT
public:

    explicit PianoRollStaff(QObject* parent = nullptr, QString staffName = "", bool isOpen = false,
                            bool isFirst = false, bool isNewBar = false, int midiKey = 0, int index = 0, bool isNote = false);
    ~PianoRollStaff() {};

    inline void setSize(int x, int y, int w, int h){
        this->setRect(0,0,w,h);
        this->setPos(x,y);
    }

    void AddNote(int x, int y);
    static void LoadNote(int x, int y, float z);
    void CustomNote(int x, int y);
    void DeleteNote();
    static void UnloadNote();

    static void AddMeasures();
    static void DeleteMeasures(int numMea);

    static QGraphicsScene* myScene;
    static QObject* myParent;
    static int noteLength;
    static bool PianoInteract;
    static int numBlocks;

private:
    QString myStaffName;
    QList<QColor> myColors;
    //ToneGen tongen;
    bool isOpen;
    bool isFirst;
    bool isNewBar;
    bool isHovering;
    bool isChecked;
    bool myNote;
    int myMidiKey;
    int myIndex;

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);

    inline void hoverEnterEvent(QGraphicsSceneHoverEvent*)
        {
            isHovering = true;
            this->scene()->update(x(), y(), rect().x(), rect().y());
        }
        inline void hoverLeaveEvent(QGraphicsSceneHoverEvent*)
        {
            isHovering = false;
            this->scene()->update(x(), y(), rect().x(), rect().y());
        }

        void mousePressEvent(QGraphicsSceneMouseEvent* event);
        //void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};

/*!
 * \brief Creates multiple PianoRollStaff[s], places them in their correct positons, and keeps track of
 *   what key maps to what note.
 */
class PianoRoll : public QGraphicsView
{
    Q_OBJECT

public:
    explicit PianoRoll(QWidget* parent = nullptr);
    virtual ~PianoRoll() {};
    static QMap<QString, int> noteNames;
    //inline PianoRollStaff* staff(int num) { return staffs.value(num); }

private:
    void addOpenStaff(QGraphicsScene* scene, QString staffName);
    void addLineStaff(QGraphicsScene* scene, QString staffName);
    int k;
    int curKey;
    int curO;
    int curC;
};


#endif // PIANOROLL_H
