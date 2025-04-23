#ifndef MEDIA_LIST_CONTROLLER_H
#define MEDIA_LIST_CONTROLLER_H

#include "../view/MediaListView.h"

class MediaListController{
    private:
        MediaListView medialistview;
    public:
        vector<string> showMediaList();
};
#endif // !