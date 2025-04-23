#include "MetadataController.h"
#include <cstdlib>
#include <iostream>
using namespace std;

void MetadataController::showMetadata(const string& filepath) {
    string title, artist, album, genre, comment;
    unsigned int year;
    int duration;

    system("clear");
    if (model.readMetadata(filepath, title, artist, album, genre, comment, year, duration)) {
        view.displayMetadata(filepath, title, artist, album, genre, comment, year, duration);
    } else {
        cout << "Cannot read metadata from file: " << filepath << "\n";
    }
}

void MetadataController::editMetadata(const string& filepath) {
    auto [title, artist, album, genre, comment, year] = view.promptEditMetadata();

    system("clear");
    if (model.writeMetadata(filepath, title, artist, album, genre, comment, year)) {
        cout << "Metadata saved successfully.\n";
    } else {
        cout << "Failed to save metadata.\n";
    }
}