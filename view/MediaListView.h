#ifndef MEDIA_LIST_VIEW_H
#define MEDIA_LIST_VIEW_H

#include "../model/FileBrowser.h"

class MediaListView{
    public:
        void displayMediaList(string dir);
        string inputDir();
};

#endif 