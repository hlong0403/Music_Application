#include "VideoMetadataController.h"

#include <iostream>
#include <cstdlib>
using namespace std;

void VideoMetadataController :: showVideoMetadata(const string& filepath) {
    string title, artist, album, genre, comment, year, codec_name;
    int width, height;
    double duration_seconds;

    system("clear");
    if (model.readMetadata(filepath, title, artist, album, genre, comment, year, codec_name, width, height, duration_seconds)) {
        view.displayVideoMetadata(filepath, title, artist, album, genre, comment, year, codec_name, width, height, duration_seconds);
    } else {
        cout << "Cannot read metadata from file: " << filepath << "\n";
    }
}

