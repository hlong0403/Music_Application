#ifndef PLAYLISTCONTROLLER_H
#define PLAYLISTCONTROLLER_H

#include "../model/PlaylistModel.h"
#include "../view/PlaylistView.h"
#include <vector>

using namespace std;

class PlaylistController {
    private:
        PlaylistView view;
        PlaylistModel playlist;
    public:
        static vector<string> listPlaylists();
        PlaylistController();
        static PlaylistModel loadPlaylist(const string& name);
        void displayPlaylistList();
        void addNewPlaylist();
        void displaySongsInPlaylist(const string& name, const vector<string>& songs);
        void deleteSong(PlaylistModel pl);
        void addSong(PlaylistModel pl);
};

#endif
