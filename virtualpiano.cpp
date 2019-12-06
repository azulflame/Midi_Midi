/*
 * Raging MIDI (https://github.com/waddlesplash/ragingmidi).
 *
 * Copyright (c) 2012-2013 WaddleSplash & contributors (see AUTHORS.txt).
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "virtualpiano.h"
#include "common.h"

VirtualPianoKey::VirtualPianoKey(QObject* parent, int midiKey, QString noteName, bool isBlackKey)
    : QObject(parent), QGraphicsRectItem(nullptr)
{
    isBlack = isBlackKey;
    if (isBlack) {
        setZValue(1);
    }
    isHovering = false;
    isClicking = false;
    this->setAcceptHoverEvents(true);
    this->setAcceptedMouseButtons(Qt::LeftButton);

    myMidiKey = midiKey;
    myNoteName = noteName;
}

void VirtualPianoKey::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    isClicking = true;
    this->update();
    GlobalToneGenPntr->addTone(myMidiKey+57);
    GlobalToneGenPntr->playTone(myMidiKey+57);
}
void VirtualPianoKey::mouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
    isClicking = false;
    this->update();
    GlobalToneGenPntr->stopTone(myMidiKey+57);
}

void VirtualPianoKey::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    int x = rect().x();
    int y = rect().y();
    int w = rect().width();
    int h = rect().height();

    painter->setPen(Qt::gray);

    if (isHovering && !isClicking) {
        painter->setBrush(QColor("#8080ff"));
    } else if (isClicking) {
        painter->setBrush(Qt::blue);
    } else {
        if (isBlack) {
            painter->setBrush(Qt::black);
        }
         else {
            painter->setBrush(Qt::white);
        }
    }

    painter->drawRect(rect());

    if (isBlack) {
        return;
    }

    // Draw the key name (not for Black keys)
    painter->setPen(Qt::black);
    QFont f = painter->font();
    f.setPointSize(8);
    painter->setFont(f);
    painter->drawText(x + 42, y + 13, myNoteName);
}

VirtualPiano::VirtualPiano(QWidget* parent)
    : QGraphicsView(parent)
{
    this->setMinimumHeight(80);
    this->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QGraphicsScene* scene = new QGraphicsScene(this);
    this->setScene(scene);
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    k = 0;
    curKey = 51;
    for (int i = 8; i > 0; i--) {
        QString num = QString::number(i);
        QString firstC = QString::number(i+1);
        addWhiteKey(scene, "C"+firstC);
        addWhiteKey(scene, "B"+num); // or Db
        addBlackKey(scene, "Bb");
        addWhiteKey(scene, "A"+num); // or Eb
        addBlackKey(scene, "Ab");
        addWhiteKey(scene, "G"+num);
        addBlackKey(scene, "Gb"); // or Gb
        addWhiteKey(scene, "F"+num);
        addWhiteKey(scene, "E"+num); // or Ab
        addBlackKey(scene, "Eb");
        addWhiteKey(scene, "D"+num); // or Bb
        addBlackKey(scene, "Db");
    }

}

void VirtualPiano::addWhiteKey(QGraphicsScene* scene, QString noteName)
{
    VirtualPianoKey* newKey = new VirtualPianoKey(this, curKey, noteName, false);
    qreal loc = k * 20;
    newKey->setSize(0, loc, 60, 20);
    scene->addItem((QGraphicsItem*)newKey);
    keys.insert(curKey, newKey);
    k += 1;
    curKey -= 1;
}

void VirtualPiano::addBlackKey(QGraphicsScene* scene, QString noteName)
{
    VirtualPianoKey* newKey = new VirtualPianoKey(this, curKey, noteName, true);
    qreal loc = (k * 20)-5;
    newKey->setSize(0, loc, 40, 10);
    scene->addItem((QGraphicsItem*)newKey);
    keys.insert(curKey, newKey);
    curKey -= 1;
}
