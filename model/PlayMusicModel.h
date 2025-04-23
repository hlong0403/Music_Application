#ifndef PLAY_MUSIC_MODEL_H
#define PLAY_MUSIC_MODEL_H

#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

class PlayMusicModel {
private:
    vector<string> playlist;
    int currentIndex;
    atomic<bool> playing;
    atomic<bool> paused;
    atomic<bool> stopRequested;
    atomic<bool> skipToPrevious;
    atomic<bool> skipToNext;
public:
    PlayMusicModel(const vector<string>& songs);
    PlayMusicModel();
    ~PlayMusicModel();
    void setPlaylist(const vector<string>& songs);

    const vector<string>& getPlaylist() const;
    int getCurrentIndex();
    void setCurrentIndex(int index);
    

    void setPlaying(bool value);
    void setPaused(bool value);
    void setStopRequested(bool value);
    void setSkipToPrevious(bool value);
    void setSkipToNext(bool value);

    bool isStopRequested() const;
    bool isPaused() const;
    bool isSkipToPrevious() const;
    bool isSkipToNext() const;
    bool isPlaying() const;

};

#endif
