#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include "song.h"

class FileManager
{
public:
    FileManager();
    void save_file(Song current_song);
    Song load_file();
    void export_file(Song current_song, std::string extension);
    Song import_file();

    std::string file_name;
};

#endif // FILEMANAGER_H
