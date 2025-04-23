#ifndef VIDEO_METADATA_MODEL_H
#define VIDEO_METADATA_MODEL_H
#include <string>
using namespace std;

class VideoMetadataModel {
public:
    VideoMetadataModel();

    bool readMetadata(const string& filepath,
                      string& title, string& artist,
                      string& album, string& genre,
                      string& comment, string& year,
                      string& codec_name, int& width, int& height,
                      double& duration_seconds);
};
#endif // !1

