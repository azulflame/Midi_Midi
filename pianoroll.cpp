#include "pianoroll.h"
#include "song.h"
#include "common.h"
//#include "ui_pianoroll.h"
#include <vector>

QGraphicsScene* PianoRollStaff::myScene;
vector<PianoRollStaff*> PianoRollStaff::uiNoteVector;
QMap<int, QString> PianoRoll::noteNames;
int PianoRollStaff::numBlocks = 96;
bool PianoRollStaff::contextSwitch = false;
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

void PianoRollStaff::AddNote(){
    PianoRollStaff *newNote;
    newNote = new PianoRollStaff(this, myStaffName, false, true, false, myMidiKey, 0, true);
    int length = noteLength*20;
    newNote->setSize(this->x(),this->y(),length,20);
    myScene->addItem((QGraphicsItem*)newNote);
    uiNoteVector.push_back(newNote);

    length = length/20;
    int x = this->x()/20;
    length = x + length;
    while(length > numBlocks) AddMeasures();
    GlobalMainWindow->current_song.tracks.at(0).addNote(myMidiKey+57, noteLength, this->x());
}//creates a basic note based on selected input size


void PianoRollStaff::LoadNote(int x, int y, float z){
    PianoRollStaff *newNote;
    QString name;
   // uiNoteVector.push_back(newNote);
    int yPos = 1900 -((y -13) * 20); // convert from midikey to yPos
    if(PianoRoll::noteNames[y-57].contains("b")) name = "";
    else name = PianoRoll::noteNames[y-57];
    newNote = new PianoRollStaff(myParent, name, false, true, false, y-57, 0, true);
    qDebug() << "y"<< y;
    float length = z*20;
    newNote->setSize(x,yPos,length,20);
    myScene->addItem((QGraphicsItem*)newNote);
    uiNoteVector.push_back(newNote);

    length = length/20;
    x = x/20;
    length = x + length;
    while(length > numBlocks) AddMeasures();
}//creates a basic note based on selected input size

void PianoRollStaff::DeleteNote(){
    myScene->removeItem(this);
    delete this;
}

void PianoRollStaff::UnloadNote(){

    for(int i = (uiNoteVector.size() - 1); i >= 0; i--)
    {
        myScene->removeItem((QGraphicsItem*)uiNoteVector.at(i));
        uiNoteVector.erase(uiNoteVector.begin() + i);
    }

    return;
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
    bool firstBlock;
    QString name;

    for(int i = 0; i < 16; i++){
        for(int j = 8; j > 0; j--){
            for(int k = 0; k < 6; k++){
                if(i == 0) firstBlock = true;
                else firstBlock = false;

                if(i == 15) lastBlock = true;
                else lastBlock = false;

                if(PianoRoll::noteNames[curKey].contains("b")) name = "";
                else name = PianoRoll::noteNames[curKey];

                loc = l*20;
                newLine = new PianoRollStaff(myParent, name, true, firstBlock, lastBlock, curKey);
                newLine->setSize(numBlocks*20, loc, 20, 20);
                myScene->addItem((QGraphicsItem*)newLine);
                l++;
                curKey--;

                if(PianoRoll::noteNames[curKey].contains("b")) name = "";
                else name = PianoRoll::noteNames[curKey];

                loc = l*20;
                newLine = new PianoRollStaff(myParent, name, false, firstBlock, lastBlock, curKey);
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

void PianoRollStaff::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    if(contextSwitch){
        contextSwitch = false;
        return;
     }
    //if(!PianoInteract) return;
    QMenu menu;

    QAction action1("Add Measures", this);
    connect(&action1, &QAction::triggered, [this]() {
        MAdder dialog;
        dialog.setModal(true);
        dialog.exec();
     });
    menu.addAction(&action1);

    QAction action2("Add Note", this);
    connect(&action2, &QAction::triggered, [this]() {
        NAdder dialog(nullptr, this);
        dialog.setModal(true);
        dialog.exec();
     });
    menu.addAction(&action2);

    QAction action3("Add Tempo", this);
    connect(&action3, &QAction::triggered, [this]() {
        TAdder dialog;
        dialog.setModal(true);
        dialog.exec();
     });
    menu.addAction(&action3);

    menu.exec(event->screenPos());
}

void PianoRollStaff::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //GlobalToneGenPntr->playTone(myMidiKey+57);*/ // added 57 because A4 is 0 on his scale

    if(event->buttons() == Qt::RightButton && myNote == false)
        return;
    if(!PianoInteract) return;

    if(event->buttons() == Qt::RightButton && myNote == true)
    {
        GlobalMainWindow->current_song.tracks.at(0).removeNote(myMidiKey+57, this->x());
        DeleteNote();
        contextSwitch = true;
    }
    else if(event->buttons() == Qt::LeftButton && myNote == false)
    {
        int end_tick;

        AddNote();

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
        painter->setBrush(QColor("#780000"));
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
            painter->setPen(QColor("#780000"));
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
        noteNames.insert(curKey, "C"+firstC);
        addOpenStaff(scene, "C"+firstC);
        noteNames.insert(curKey, "B"+num);
        addLineStaff(scene, "B"+num);
        noteNames.insert(curKey, "Bb"+num);
        addOpenStaff(scene, "");//Bb
        noteNames.insert(curKey, "A"+num);
        addLineStaff(scene, "A"+num);
        noteNames.insert(curKey, "Ab"+num);
        addOpenStaff(scene, "");//Ab
        noteNames.insert(curKey, "G"+num);
        addLineStaff(scene, "G"+num);
        noteNames.insert(curKey, "Gb"+num);
        addOpenStaff(scene, "");//Gb
        noteNames.insert(curKey, "F"+num);
        addLineStaff(scene, "F"+num);
        noteNames.insert(curKey, "E"+num);
        addOpenStaff(scene, "E"+num);
        noteNames.insert(curKey, "Eb"+num);
        addLineStaff(scene, "");//Eb
        noteNames.insert(curKey, "D"+num);
        addOpenStaff(scene, "D"+num);
        noteNames.insert(curKey, "Db"+num);
        addLineStaff(scene, "");//Db
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
        else if(i > 0 && j == 1) newLine = new PianoRollStaff(this, staffName, true, true, false, curKey, curC);
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
        else if(i > 0 && j == 1) newLine = new PianoRollStaff(this, staffName, false, true, false, curKey, curC);
        else newLine = new PianoRollStaff(this, staffName, false, false, false, curKey, curC);
        newLine->setSize(i*20, loc, 20, 20);
        scene->addItem((QGraphicsItem*)newLine);
        j++;
    }//creates 100 initial 16th blocks
    k += 1;
    curKey -= 1;
    curC += 1;
}
