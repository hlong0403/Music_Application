#include "PlayMusicModel.h"
#include "FileBrowser.h"
#include "Utils.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <taglib/fileref.h>  
#include <taglib/audioproperties.h>
#include <iomanip>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>


using namespace std;

PlayMusicModel :: PlayMusicModel(const vector<string>& songs)
    : playlist(songs), currentIndex(0), playing(false), paused(false), 
    stopRequested(false), skipToPrevious(false), skipToNext(false) {}

PlayMusicModel :: ~PlayMusicModel() {
}

PlayMusicModel :: PlayMusicModel(){}

const vector<string>& PlayMusicModel::getPlaylist() const {
    return playlist;
}

int PlayMusicModel:: getCurrentIndex(){
    return currentIndex;
}

void PlayMusicModel :: setCurrentIndex(int index) {
    currentIndex = index;
}


void PlayMusicModel::setPlaylist(const vector<string>& songs) {
    playlist = songs;
    currentIndex = 0;
}

void PlayMusicModel::setPlaying(bool value) {
    playing.store(value);
}

void PlayMusicModel::setPaused(bool value) {
    paused.store(value);
}

void PlayMusicModel::setStopRequested(bool value) {
    stopRequested.store(value);
}

void PlayMusicModel::setSkipToPrevious(bool value) {
    skipToPrevious.store(value);
}

void PlayMusicModel::setSkipToNext(bool value) {
    skipToNext.store(value);
}

bool PlayMusicModel::isStopRequested() const {
    return stopRequested.load();
}

bool PlayMusicModel::isSkipToPrevious() const {
    return skipToPrevious.load();
}

bool PlayMusicModel::isSkipToNext() const {
    return skipToNext.load();
}

bool PlayMusicModel::isPlaying() const {
    return playing.load();
}

bool PlayMusicModel::isPaused() const {
    return paused.load();
}
