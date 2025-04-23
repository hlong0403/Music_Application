#ifndef VIDEO_METADATA_CONTROLLER_H
#define VIDEO_METADATA_CONTROLLER_H

#include "../model/VideoMetadataModel.h"
#include "../view/VideoMetadataView.h"

#include <string>
using namespace std;

class VideoMetadataController {
    private:
        VideoMetadataModel model;
        VideoMetadataView view;

    public:
        void showVideoMetadata(const string& filepath);
};

#endif
