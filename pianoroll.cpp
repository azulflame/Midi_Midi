#include "pianoroll.h"
#include "song.h"
#include "common.h"
//#include "ui_pianoroll.h"
#include <vector>
QGraphicsScene* PianoRollStaff::myScene;
QMap<QString, int> PianoRoll::noteNames;
int PianoRollStaff::numBlocks = 96;
QObject* PianoRollStaff::myParent;

PianoRollStaff::PianoRollStaff(QObject* parent, QString staffName, bool isOpenStaff, bool isMyFirst,
                               bool isMyNewBar, int midiKey, int index, bool isNote)
    : QObject(parent), QGraphicsRectItem(nullptr)
{
    myStaffName = staffName;
    isOpen = isOpenStaff;
    isFirst = isMyFirst;
    isNewBar = isMyNewBar;
    myMidiKey = midiKey;
    myIndex = index;
    myNote = isNote;
    if(myNote){
        setZValue(1);
    }//paints on top of other rect if note


    isHovering = false;
    if(myNote) isChecked = true;
    else isChecked = false;
    this->setAcceptHoverEvents(true);
}

void PianoRollStaff::AddNote(int x, int y){
    PianoRollStaff *newNote;
    newNote = new PianoRollStaff(this, myStaffName, false, true, false, myMidiKey, 0, true);
    int length = noteLength*20;
    newNote->setSize(x,y,length,20);
    myScene->addItem((QGraphicsItem*)newNote);

    length = length/20;
    x = x/20;
    length = x + length;
    if(length > numBlocks) AddMeasures();
}//creates a basic note based on selected input size


void PianoRollStaff::LoadNote(int x, int y){
    qDebug() << y;
    PianoRollStaff *newNote;
    newNote = new PianoRollStaff(nullptr, "" , false, true, false, y-57, 0, true);
    int length = noteLength*20;
    newNote->setSize(x,y,length,20);
    myScene->addItem((QGraphicsItem*)newNote);

    length = length/20;
    x = x/20;
    length = x + length;
    if(length > numBlocks) AddMeasures();
}//creates a basic note based on selected input size

void PianoRollStaff::DeleteNote(){
    myScene->removeItem(this);

    //add what you need to delete note from song


    delete this;
}

void PianoRollStaff::CustomNote(int x, int y){
    //Creating a custom size not
}

void PianoRollStaff::AddMeasures(){
    PianoRollStaff* newLine;
    int l = 0;
    int loc;
    int curKey = 51;
    bool lastBlock;

    for(int i = 0; i < 16; i++){
        for(int j = 8; j > 0; j--){
            for(int k = 0; k < 6; k++){
                if(i == 15) lastBlock = true;
                else lastBlock = false;

                loc = l*20;
                newLine = new PianoRollStaff(myParent, "", true, false, lastBlock, curKey);
                newLine->setSize(numBlocks*20, loc, 20, 20);
                myScene->addItem((QGraphicsItem*)newLine);
                l++;
                curKey--;

                loc = l*20;
                newLine = new PianoRollStaff(myParent, "", false, false, lastBlock, curKey);
                newLine->setSize(numBlocks*20, loc, 20, 20);
                myScene->addItem((QGraphicsItem*)newLine);
                l++;
                curKey--;
            }
        }
        numBlocks++;
        l = 0;
        curKey = 51;
     }
}

void PianoRollStaff::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //GlobalToneGenPntr->playTone(myMidiKey+57);*/ // added 57 because A4 is 0 on his scale

    if(!PianoInteract) return;

    if(event->buttons() == Qt::RightButton && myNote == true)
    {
        GlobalMainWindow->current_song.tracks.at(0).removeNote(myMidiKey+57, this->x());
        DeleteNote();
    }
    else if(event->buttons() == Qt::LeftButton && myNote == false)
    {
        int end_tick;

        GlobalMainWindow->current_song.tracks.at(0).addNote(myMidiKey+57, noteLength, this->x());
        AddNote(this->x(), this->y());

        end_tick = (this->x() + (noteLength*20));
        qDebug() << GlobalMainWindow->last_tick;
        qDebug() << end_tick;

        if(GlobalMainWindow->last_tick < end_tick)
        {
            GlobalMainWindow->last_tick = end_tick;
        }
    }
    update();
}//plays note pertaining to grid area and adds note if notation mode is on

void PianoRollStaff::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    int x = rect().x();
    int y = rect().y();
    int w = rect().width();
    int h = rect().height();

    painter->setPen(Qt::gray);

    if(isHovering && !isChecked){
        if(myNote) painter->setBrush(Qt::green);
        else painter->setBrush(QColor("#8080ff"));
    }//changes color for block hovered on
    else if(isChecked){
        painter->setBrush(Qt::blue);
    }//sets color for note
    else{
        if(isOpen){
            painter->setBrush(Qt::gray);
        }else{
         painter->setBrush(Qt::black);
        }
    }//alternates the color of staff


    painter->drawRect(rect());
    if(!myNote){
        if(isNewBar){
            painter->setPen(Qt::red);
            painter->drawLine(x + 20, y, 20, 20);
        }else{
            painter->setPen(Qt::blue);
            painter->drawLine(x + 20, y, 20, 20);
        }
    }//draws grid lines will skip if note is created

    //will draw note names for frist column and for notes
    if(!isFirst) return;
    painter->setPen(Qt::white);
    QFont f = painter->font();
    f.setPointSize(8);
    painter->setFont(f);
    painter->drawText(x, y + 13, myStaffName);
}

PianoRoll::PianoRoll(QWidget* parent)
    : QGraphicsView(parent)
{
    //setting up graphic scene
    this->setMinimumHeight(80);
    this->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    QGraphicsScene* scene = new QGraphicsScene(this);
    this->setScene(scene);
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    k = 0;
    curKey = 51;
    curO = 0;
    curC = 0;
    for (int i = 8; i > 0; i--) {
        QString num = QString::number(i);
        QString firstC = QString::number(i+1);
        addOpenStaff(scene, "C"+firstC);
        noteNames.insert("C"+num, curKey);
        addLineStaff(scene, "B"+num);
        noteNames.insert("B"+num, curKey);
        addOpenStaff(scene, "");//Bb
        noteNames.insert("Bb"+num, curKey);
        addLineStaff(scene, "A"+num);
        noteNames.insert("A"+num, curKey);
        addOpenStaff(scene, "");//Ab
        noteNames.insert("Ab"+num, curKey);
        addLineStaff(scene, "G"+num);
        noteNames.insert("G"+num, curKey);
        addOpenStaff(scene, "");//Gb
        noteNames.insert("Gb"+num, curKey);
        addLineStaff(scene, "F"+num);
        noteNames.insert("F"+num, curKey);
        addOpenStaff(scene, "E"+num);
        noteNames.insert("E"+num, curKey);
        addLineStaff(scene, "");//Eb
        noteNames.insert("Eb"+num, curKey);
        addOpenStaff(scene, "D"+num);
        noteNames.insert("D"+num, curKey);
        addLineStaff(scene, "");//Db
        noteNames.insert("Db", curKey);
    }//creates staffs and creates a map of note names with their key for Tongen

    PianoRollStaff::myScene = scene;
    PianoRollStaff::myParent = this;
    qDebug() << "Blocks: " << k;
}

void PianoRoll::addOpenStaff(QGraphicsScene* scene, QString staffName)
{
    PianoRollStaff* newLine;
    qreal loc = k * 20;
    int j = 1;

    for(int i = 0; i < 96; i++){
        if(i == 0) newLine = new PianoRollStaff(this, staffName, true, true, false, curKey, curO);
        else if(j == 16){
            newLine = new PianoRollStaff(this, staffName, true, false, true, curKey, curO);
            j = 0;
        }
        else newLine = new PianoRollStaff(this, staffName, true, false, false, curKey, curO);
        newLine->setSize(i*20, loc, 20, 20);
        scene->addItem((QGraphicsItem*)newLine);
        j++;
    }//creates 100 initial 16th blocks
    k += 1;
    curKey -= 1;
    curO += 1;
}

void PianoRoll::addLineStaff(QGraphicsScene* scene, QString staffName)
{
    PianoRollStaff* newLine;
    qreal loc = k * 20;
    int j = 1;

    for(int i = 0; i < 96; i++){
        if(i == 0) newLine = new PianoRollStaff(this, staffName, false, true, false, curKey, curC);
        else if(j == 16){
            newLine = new PianoRollStaff(this, staffName, false, false, true, curKey, curC);
            j = 0;
        }
        else newLine = new PianoRollStaff(this, staffName, false, false, false, curKey, curC);
        newLine->setSize(i*20, loc, 20, 20);
        scene->addItem((QGraphicsItem*)newLine);
        j++;
    }//creates 100 initial 16th blocks
    k += 1;
    curKey -= 1;
    curC += 1;
}
