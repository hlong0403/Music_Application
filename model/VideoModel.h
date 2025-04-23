#ifndef VIDEO_MODEL_H
#define VIDEO_MODEL_H

#include "VideoMetadataModel.h"
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
using namespace std;

class VideoModel {
private:
    VideoMetadataModel metadata;
    thread playThread;
    bool running;
    int pid = -1;

    chrono::steady_clock::time_point startTime;
    chrono::steady_clock::time_point pauseTime;
    atomic<bool> paused = false;
    int elapsedBeforePause = 0;

    atomic<int> durationInSec;

    void playProcess(const string& filepath, int volume);

public:
    VideoModel();
    ~VideoModel();

    void play(const string& filepath, int volume = 64);
    void stop();
    void pause();
    void resume();
    bool isRunning() const;

    int getElapsedSeconds();
    int getTotalDuration(const string& filepath) ;
    bool isPaused() const;

};

#endif
