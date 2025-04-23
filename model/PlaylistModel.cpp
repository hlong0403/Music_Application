#include "PlaylistModel.h"
#include <fstream>
#include <iostream>

using namespace std;

PlaylistModel :: PlaylistModel(){}

PlaylistModel::PlaylistModel(const string& name) : name(name) {}

const string& PlaylistModel::getName() const {
    return name;
}

const vector<string>& PlaylistModel::getSongs() const {
    return songs;
}

void PlaylistModel::addSong(const string& path) {
    songs.push_back(path);
}

void PlaylistModel::removeSong(int index) {
    if (index >= 0 && index < songs.size()) {
        songs.erase(songs.begin() + index);
    }
}

void PlaylistModel::listSongs() const {
    cout << "Playlist: " << name << "\n";
    for (int i = 0; i < songs.size(); ++i) {
        cout << i + 1 << ". " << songs[i] << "\n";
    }
}

bool PlaylistModel::saveToFile() const {
    ofstream out("playlists/" + name + ".txt");
    if (!out.is_open()) return false;
    for (const auto& song : songs) {
        out << song << "\n";
    }
    return true;
}

bool PlaylistModel::loadFromFile() {
    ifstream in("playlists/" + name + ".txt");
    if (!in.is_open()) return false;

    songs.clear();
    string line;
    while (getline(in, line)) {
        if (!line.empty())
            songs.push_back(line);
    }
    return true;
}
