#ifndef METADATAVIEW_H
#define METADATAVIEW_H

#include <string>
using namespace std;

class MetadataView {
public:
    MetadataView();
    void displayMetadata(
        const string& filepath,
        const string& title,
        const string& artist,
        const string& album,
        const string& genre,
        const string& comment,
        unsigned int year,
        int duration = -1
    );
    tuple<string, string, string, string, string, unsigned int>
    promptEditMetadata();
};

#endif
