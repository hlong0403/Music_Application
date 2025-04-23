#ifndef VIDEO_VIEW_H
#define VIDEO_VIEW_H

#include <iostream>

class VideoView {
public:
    void showControls();
    void notifyThreadStart();
    void displayKeyPressed(char c);
};

#endif
