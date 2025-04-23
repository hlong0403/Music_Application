#ifndef PLAYMUSICCONTROLLER_H
#define PLAYMUSICCONTROLLER_H

#include <string>
#include <thread>
#include <atomic>

#include "../model/PlayMusicModel.h"
#include "../view/PlayMusicView.h"
#include "../controller/VideoController.h"

using namespace std;

class PlayMusicController {
private:
    PlayMusicModel playModel;
    VideoModel videoModel;
    PlayMusicView playView;
    thread playThread;
    Mix_Music* music = nullptr;
    string currentFile;

public:
    PlayMusicController();
    ~PlayMusicController();
    void playbackLoop();
    void stop();
    void start();
    Mix_Music* getMusic();
    bool load(const string& filepath);
    bool isPlaying() const;

    void runMusic(vector<string> songs);
    void displayMediaControl();
};

#endif
