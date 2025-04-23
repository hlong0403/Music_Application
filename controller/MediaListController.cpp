#include "MediaListController.h"
#include <iostream>

vector<string> MediaListController :: showMediaList(){
    string name = medialistview.inputDir();
    cout<<name<<endl;
    vector<string> files = FileBrowser::findMediaFiles(name);
    medialistview.displayMediaList(name);
    return files;
}