#include "filemanager.h"
#include <string>
#include <map>
#include <vector>
#include <QFile>
#include <QDialog>
#include "song.h"
#include "track.h"
#include "midinote.h"
#include "common.h"
#include "pianoroll.h"
#include <QFileDialog>
#include <QTranslator>
#include "Midi_import/MidiFile.h"
#include <cmath>
#include "tadder.h"
#include "pianoroll.h"

/* DISCLAIMER: I dont remember if we need an overloaded operator to set
   the current song equal to the songer returned, if we do i will take care of it
       - EJ <3
*/

FileManager::FileManager()
{

}
void FileManager::save_file(Song current_song)
{
    /* Save ya stuff in here */
    QString path = qApp->applicationDirPath();
    QDir dir;
    //::PianoInteract = false;
    //PianoRollStaff::UnloadNote();
    QString fileName = QFileDialog::getSaveFileName(GlobalMainWindow, "Save Song", path+"/untitled.smf", "MIDI_MIDI (*.smf)");
    QFile file(fileName);
    if(!dir.exists(path))
    {
        dir.mkpath(path);
        qDebug() << "directory now exists";
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"file now exists";
    }

    QTextStream fout(&file);
    fout << GlobalMainWindow->last_tick << endl;
    //loop
    for(int i = 0; i <= GlobalMainWindow->last_tick; i+=20)
    {
        std::map<int, tone_vector>::iterator track_iterator;

        //Play notes
        track_iterator = GlobalMainWindow->current_song.tracks.at(0).note_map.find(i);

        if(track_iterator != GlobalMainWindow->current_song.tracks.at(0).note_map.end())
        {

            for(int j = 0; j < GlobalMainWindow->current_song.tracks[0].note_map.at(i).size(); j++)
            {
                fout << i //start time
                << "," << GlobalMainWindow->current_song.tracks[0].note_map.at(i)[j].value //note
                << "," << GlobalMainWindow->current_song.tracks[0].note_map.at(i)[j].duration << endl; //length

            }

        }
    }
    qDebug() << "finished.";
    qDebug() << "App path : " << path;
    file.close();
}
void FileManager::load_file()
{
    Song song_data;
    QString path = qApp->applicationDirPath();
    QDir dir;
    //PianoRollStaff::PianoInteract = false;
    PianoRollStaff::UnloadNote();
    QString fileName = QFileDialog::getOpenFileName(GlobalMainWindow,
            "Load Song", path,
            "MIDI_MIDI (*.smf)");
    QFile file(fileName);
    int i = 0;

    if(dir.exists(path))
    {
        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream fin(&file);

            GlobalMainWindow->current_song.tracks[0].note_map.clear();
            while(!fin.atEnd())
            {
                QString line = fin.readLine();
                if(i == 0)
                    GlobalMainWindow->last_tick = line.toInt();

                else if(!(line.isNull()) && !(line[0] == '\n') && line.contains(',') && i != 0)
                {
                    QStringList list = line.split(",");
                    qDebug() << "start: " <<list.at(0) << "value: "<< list.at(1) << "duration: " << list.at(2);
                    GlobalMainWindow->current_song.tracks.at(0).addNote(list.at(1).toInt(), list.at(2).toFloat(), list.at(0).toInt());
                    PianoRollStaff::LoadNote(list.at(0).toInt(), list.at(1).toInt(), list.at(2).toFloat());
                }
                i++;
            }
        }
    }
    /* Load ya data in here */



    file.close();
}
void FileManager::export_file()
{
    QString path = qApp->applicationDirPath();
    QDir dir;
    //PianoRollStaff::PianoInteract = false;

    QString fileName = QFileDialog::getSaveFileName(GlobalMainWindow, "Save Song", path+"/untitled.mid", "MIDI_MIDI (*.mid)");
    QFile file(fileName);
    if(!dir.exists(path))
    {
        dir.mkpath(path);
        qDebug() << "directory now exists";
    }

    //loop
    smf::MidiFile mf;
    for(int i = 0; i <= GlobalMainWindow->last_tick; i+=20)
    {
        std::map<int, tone_vector>::iterator track_iterator;

        int track = 0;
        int channel = 0;
        //int instr = mf.addTimbre(track, 0, channel, 0);
        int tpq = mf.getTPQ();
        //Play notes
        track_iterator = GlobalMainWindow->current_song.tracks.at(0).note_map.find(i);

        if(track_iterator != GlobalMainWindow->current_song.tracks.at(0).note_map.end())
        {

            for(int j = 0; j < GlobalMainWindow->current_song.tracks[0].note_map.at(i).size(); j++)
            {
                int starttime = (i*mf.getTPQ()/20)/4; //start time
                int key =  GlobalMainWindow->current_song.tracks[0].note_map.at(i)[j].value; //note
                int endtime = starttime + (GlobalMainWindow->current_song.tracks[0].note_map.at(i)[j].duration * mf.getTPQ())/4; //length // might be mf.getTicksPerQuarterNote();
                mf.addNoteOn(track, starttime, channel, key, 100);
                mf.addNoteOff(track, endtime, channel, key);

            }

            mf.sortTracks();
            mf.write(fileName.toLocal8Bit().constData());

        }
    }
    qDebug() << "finished.";
    qDebug() << "App path : " << path;
    file.close();
}

void FileManager::import_file()
{
    Song song_data;
    QString path = qApp->applicationDirPath();
    QDir dir;
    //PianoRollStaff::PianoInteract = false;
    //PianoRollStaff::UnloadNote();
    QString fileName = QFileDialog::getOpenFileName(GlobalMainWindow,
            "Load Song", path,
            "Midi (*.mid)");
    QFile file(fileName);
    int track;
    int event;

    float maxTick= 0;

    if(dir.exists(path))
    {
        smf::MidiFile midfile;
        midfile.read(fileName.toLocal8Bit().constData());
        midfile.linkNotePairs();
        PianoRollStaff::UnloadNote();
        GlobalMainWindow->current_song.tracks[0].note_map.clear();
        for(track = 0; track < midfile.size(); track++)
        {
            for(event = 0; event < midfile[track].size(); event++)
            {
                if(midfile[track][event].isNoteOn())
                {
                    if(midfile[track][event].isLinked())
                    {
                        int duration = (midfile[track][event].getTickDuration()*4)/(midfile.getTicksPerQuarterNote());
                        int start = midfile[track][event].tick / midfile.getTicksPerQuarterNote();
                        int key = midfile[track][event][1];
                        if(maxTick < float(start*80 + duration))
                        {
                            maxTick = float(start*80) + duration;
                            qDebug() << maxTick;
                        }
                        GlobalMainWindow->current_song.tracks.at(0).addNote(key, duration, start*80);
                        PianoRollStaff::LoadNote(start*80, key, duration);
                    }
                }
            }
        }

    //qs.toLocal8Bit().constData();
    /* import ya data in here */
    GlobalMainWindow->last_tick = (maxTick + 80);
    return;
    }
}
