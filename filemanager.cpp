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
    QString path = qApp->applicationDirPath()+"/projects";
    QDir dir;
    QString fileName = QFileDialog::getSaveFileName(GlobalMainWindow, "Save Song", path+"/untitled.txt", "MIDI_MIDI (*.smf);;All Files (*)");
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
    QString path = qApp->applicationDirPath()+"/projects";
    QDir dir;
    QString fileName = QFileDialog::getOpenFileName(GlobalMainWindow,
            "Load Song", "",
            "MIDI_MIDI (*.smf);;All Files (*)");
    QFile file(fileName);
    int i = 0;

    if(dir.exists(path))
    {
        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream fin(&file);
            PianoRollStaff::UnloadNote();
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
void export_file(Song current_song, std::string extension)
{
    /* export ya data in here */
}
Song import_file()
{
    Song song_data;
    /* import ya data in here */

    return song_data;
}
