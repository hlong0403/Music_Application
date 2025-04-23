#ifndef VIDEO_METADATA_VIEW_H
#define VIDEO_METADATA_VIEW_H
#include <string>
using namespace std;

class VideoMetadataView {
public:
    VideoMetadataView();
    void displayVideoMetadata(
        const string& filepath,
                      string& title, string& artist,
                      string& album, string& genre,
                      string& comment, string& year,
                      string& codec_name, int& width, int& height,
                      double& duration_seconds
    );
};

#endif // !
