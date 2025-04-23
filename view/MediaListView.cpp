#include "MediaListView.h"
#include <iostream>
#include <cstdlib>

void MediaListView :: displayMediaList(string dir){
    vector<string> mediaFiles = FileBrowser::findMediaFiles(dir);
    int total = mediaFiles.size();

    cout << endl << "Found " << total << " media file(s).\n";

    int page = 0;
    const int pageSize = 25;

    while (page * pageSize < total) {
        cout << "\nPage " << (page + 1) << "\n";
        for (int i = page * pageSize; i < min((page + 1) * pageSize, total); ++i) {
            cout << i + 1 << ". " << mediaFiles[i] << "\n";
        }
        if ((page + 1) * pageSize >= total) break;

        cout << "\nPress Enter to see next page...";
        cin.get();
        system("clear");
        ++page;
    }
}

string MediaListView::inputDir() {
    string dir;
    system("clear");
    cout << "Enter directory to scan (default: .): ";
    getline(cin, dir);

    if (dir.empty()) {
        dir = ".";
    }

    return dir;
}
