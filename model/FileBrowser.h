#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <string>
#include <vector>

using namespace std;

class FileBrowser {
public:
    static vector<string> findMediaFiles(const string& directory);
    static bool isMediaFile(const string& filename);
    static bool isVideoFile(const string& filename);
};

#endif
