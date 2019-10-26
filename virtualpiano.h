#ifndef VIRTUALPIANO_H
#define VIRTUALPIANO_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPaintEvent>
#include <QList>
#include <QMap>
#include <QColor>
#include <QReadWriteLock>

#include "tonegen.h"

namespace Ui
{
class VirtualPiano;
}


class VirtualPianoKey : public QObject, QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit VirtualPianoKey(QObject* parent = nullptr, int midiKey = 0, QString noteName = "",
                             bool isBlackKey = false);

    inline void setSize(int x, int y, int w, int h)
    {
        this->setRect(0, 0, w, h);
        this->setPos(x, y);
    }

    virtual ~VirtualPianoKey() {}

private:
    bool isBlack;
    bool isHovering;
    bool isClicking;
    int myMidiKey;
    QString myNoteName;
    //ToneGen tonegen;

    QList<QColor> myColors;

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
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};

/*!
 * \brief Creates 128 VirtualPianoKey[s], places them in their correct positons, and keeps track of
 *   what key maps to what note.
 */
class VirtualPiano : public QGraphicsView
{
    Q_OBJECT

public:
    explicit VirtualPiano(QWidget* parent = nullptr);

    //inline VirtualPianoKey* key(int num) { return keys.value(num); }

private:
    QMap<int, VirtualPianoKey*> keys;

    int k;
    int curKey;

    void addWhiteKey(QGraphicsScene* scene, QString noteName);
    void addBlackKey(QGraphicsScene* scene, QString noteName);
};

#endif // VIRTUALPIANO_H

