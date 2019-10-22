#include "filemanager.h"
#include <string>
#include <map>
#include <vector>
#include "song.h"
#include "track.h"
#include "note.h"

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
}
Song load_file()
{
    Song song_data;

    /* Load ya data in here */

    return song_data;
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
