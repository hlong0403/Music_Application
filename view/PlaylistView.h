#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <string>
#include <vector>

using namespace std;

class PlaylistView {
public:
    void showPlaylistList(const vector<string>& names);
    void showSongsInPlaylist(const string& name, const vector<string>& songs);
    int promptDeleteSong(const vector<string>& songs);
    vector<string> promptAddSongs();
    string inputNewName();
    char inputDeleteSong();
    char inputAddSong();
};

#endif
