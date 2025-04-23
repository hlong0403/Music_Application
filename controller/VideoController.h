#ifndef VIDEO_CONTROLLER_H
#define VIDEO_CONTROLLER_H

#include "../model/VideoModel.h"
#include "../view/VideoView.h"
#include <atomic>

class VideoController {
private:
    VideoModel vp;
    VideoView view;
    atomic<bool> stopRequested;
    atomic<bool> skipToNext;
    atomic<bool> skipToPrevious;
    atomic<bool> done;
    int volume;

public:
    VideoController();

    void playVideo(const string& file);
    bool shouldStop() const;
    bool shouldSkipNext() const;
    bool shouldSkipPrevious() const;
};

#endif
