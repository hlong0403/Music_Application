#include "PlaylistController.h"
#include <filesystem>
#include <iostream>

using namespace std;

namespace fs = filesystem;

vector<string> PlaylistController :: listPlaylists() {
    vector<string> result;
    fs::create_directory("playlists");

    for (const auto& entry : fs::directory_iterator("playlists")) {
        if (entry.path().extension() == ".txt") {
            result.push_back(entry.path().stem().string());
        }
    }
    return result;
}

PlaylistController :: PlaylistController(){

}

PlaylistModel PlaylistController::loadPlaylist(const string& name) {
    PlaylistModel p(name);
    p.loadFromFile();
    return p;
}
void PlaylistController :: displayPlaylistList(){
    vector<string> result = listPlaylists();
    view.showPlaylistList(result);
}

void PlaylistController :: addNewPlaylist(){
    string name = view.inputNewName();

    PlaylistModel pl(name);
    string song;
    cout << "Add songs (enter empty line to finish):\n";
    while (true) {
        getline(cin, song);
        if (song.empty()) break;
        pl.addSong(song);
    }

    if (pl.saveToFile()) {
        cout << "✅ Playlist saved.\n";
    }
}

void PlaylistController :: displaySongsInPlaylist(const string& name, const vector<string>& songs){
    view.showSongsInPlaylist(name, songs);
}

void PlaylistController :: deleteSong(PlaylistModel pl){
    char del = view.inputDeleteSong();
    if (del == 'y' || del == 'Y') {
        int index = view.promptDeleteSong(pl.getSongs());
        if (index != -1) {
            pl.removeSong(index);
            pl.saveToFile();
            cout << "✅ Song deleted.\n";
        }
    }
}
void PlaylistController :: addSong(PlaylistModel pl){
    char add = view.inputAddSong();
    if (add == 'y' || add == 'Y') {
        auto newSongs = view.promptAddSongs();
        for (const auto& song : newSongs) {
            pl.addSong(song);
        }
        pl.saveToFile();
        cout << "✅ Songs added and playlist updated.\n";
    }
}