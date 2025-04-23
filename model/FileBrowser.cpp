#include "FileBrowser.h"
#include <filesystem>

namespace fs = filesystem;

bool FileBrowser::isMediaFile(const string& filename) {
    string exts[] = {".mp3", ".wav", ".mp4", ".mkv", ".flac"};
    for (auto& ext : exts) {
        if (filename.size() >= ext.size() &&
            filename.substr(filename.size() - ext.size()) == ext) {
            return true;
        }
    }
    return false;
}

bool FileBrowser::isVideoFile(const string& filename) {
    string exts[] = {".mp4", ".mkv"};
    for (auto& ext : exts) {
        if (filename.size() >= ext.size() &&
            filename.substr(filename.size() - ext.size()) == ext) {
            return true;
        }
    }
    return false;
}

vector<string> FileBrowser::findMediaFiles(const string& directory) {
    vector<string> files;

    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file() && isMediaFile(entry.path().string())) {
            files.push_back(entry.path().string());
        }
    }

    return files;
}


