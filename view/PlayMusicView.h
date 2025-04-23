#ifndef PLAY_MUSIC_VIEW_H
#define PLAY_MUSIC_VIEW_H

#include "../model/PlayMusicModel.h"

class PlayMusicView{
    public:
        void showLoadSuccess(const string& filepath);
        void showLoadFail(const string& error);
        void showControlMusic();
        void showControlMedia();
};
#endif
