#ifndef PLAYLIST_MODEL_H
#define PLAYLIST_MODEL_H

#include <string>
#include <vector>

using namespace std;

class PlaylistModel {
private:
    string name;
    vector<string> songs;

public:
    PlaylistModel();
    PlaylistModel(const string& name);

    const string& getName() const;
    const vector<string>& getSongs() const;

    void addSong(const string& path);
    void removeSong(int index);
    void listSongs() const;

    bool saveToFile() const;
    bool loadFromFile();
};

#endif
