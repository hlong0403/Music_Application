#include "PlaylistView.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void PlaylistView::showPlaylistList(const vector<string>& names) {
    system("clear");
    cout << "\n=== Playlist Menu ===\n";
    if (names.empty()) {
        cout << "No playlists found.\n";
        return;
    }

    for (int i = 0; i < names.size(); ++i) {
        cout << i + 1 << ". " << names[i] << "\n";
    }
}

void PlaylistView::showSongsInPlaylist(const string& name, const vector<string>& songs) {
    system("clear");
    cout << "\n🎵 Playlist: " << name << "\n";
    if (songs.empty()) {
        cout << "(Empty playlist)\n";
        return;
    }

    for (int i = 0; i < songs.size(); ++i) {
        cout << i + 1 << ". " << songs[i] << "\n";
    }
}
int PlaylistView::promptDeleteSong(const vector<string>& songs) {
    cout << "\nEnter number of song to delete (or 0 to cancel): ";
    int index;
    cin >> index;
    cin.ignore();

    if (index < 1 || index > songs.size()) {
        cout << "Invalid choice.\n";
        return -1;
    }
    return index - 1;  // Vì hiển thị từ 1, nhưng index trong vector là 0
}
vector<string> PlaylistView::promptAddSongs() {
    vector<string> newSongs;
    cout << "\n🎧 Enter song paths to add (leave blank to finish):\n";

    string song;
    while (true) {
        getline(cin, song);
        if (song.empty()) break;
        newSongs.push_back(song);
    }
    return newSongs;
}

string PlaylistView:: inputNewName(){
    string name;
    cout << "Enter new playlist name: ";
    getline(cin, name);
    return name;
}

char PlaylistView:: inputDeleteSong(){
    cout << "Do you want to delete a song from this playlist? (y/n): ";
    char del;
    cin >> del;
    cin.ignore();
    return del;
}

char PlaylistView:: inputAddSong(){
    cout << "Do you want to add songs to this playlist? (y/n): ";
    char add;
    cin >> add;
    cin.ignore();
    return add;
}