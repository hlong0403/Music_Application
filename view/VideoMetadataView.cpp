#include "VideoMetadataView.h"
#include <iostream>
#include <limits>

using namespace std;

VideoMetadataView :: VideoMetadataView(){}

void VideoMetadataView :: displayVideoMetadata(
    const string& filepath,
    string& title, string& artist,
    string& album, string& genre,
    string& comment, string& year,
    string& codec_name, int& width, int& height,
    double& duration_seconds
) {
    cout << "\n🎧 Video Metadata for: " << filepath << "\n";
    cout << "Title   : " << title << "\n";
    cout << "Artist  : " << artist << "\n";
    cout << "Album   : " << album << "\n";
    cout << "Genre   : " << genre << "\n";
    cout << "Comment : " << comment << "\n";
    cout << "Year    : " << year << "\n";
    cout << "Codec   : " << codec_name << "\n";
    cout << "Width   : " << width << "\n";
    cout << "Height  : " << height << "\n";
    cout << "Duration: " << duration_seconds << " sec\n";
}

