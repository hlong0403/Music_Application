#ifndef METADATA_MODEL_H
#define METADATA_MODEL_H

#include <string>
#include <tuple>

using namespace std;

class MetadataModel {
public:
    MetadataModel();
    bool readMetadata(const string& filepath,
                      string& title, string& artist,
                      string& album, string& genre,
                      string& comment, unsigned int& year,
                      int& duration);

    bool writeMetadata(const string& filepath,
                       const string& title, const string& artist,
                       const string& album, const string& genre,
                       const string& comment, unsigned int year);
};

#endif
