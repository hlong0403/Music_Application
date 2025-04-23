#include "MetadataView.h"
#include <iostream>
#include <limits>

using namespace std;

MetadataView :: MetadataView(){}

void MetadataView::displayMetadata(
    const string& filepath,
    const string& title,
    const string& artist,
    const string& album,
    const string& genre,
    const string& comment,
    unsigned int year,
    int duration
) {
    cout << "\n🎧 Metadata for: " << filepath << "\n";
    cout << "Title   : " << title << "\n";
    cout << "Artist  : " << artist << "\n";
    cout << "Album   : " << album << "\n";
    cout << "Genre   : " << genre << "\n";
    cout << "Comment : " << comment << "\n";
    cout << "Year    : " << year << "\n";
    if (duration != -1)
        cout << "Duration: " << duration << " sec\n";
}

tuple<string, string, string, string, string, unsigned int>
MetadataView::promptEditMetadata() {
    string title, artist, album, genre, comment;
    unsigned int year = 0;

    cout << "\nEnter new metadata values (leave blank to keep current):\n";

    cout << "Title: ";   getline(cin, title);
    cout << "Artist: ";  getline(cin, artist);
    cout << "Album: ";   getline(cin, album);
    cout << "Genre: ";   getline(cin, genre);
    cout << "Comment: "; getline(cin, comment);

    cout << "Year: ";
    string yearInput;
    getline(cin, yearInput);
    if (!yearInput.empty())
        year = stoi(yearInput);

    return {title, artist, album, genre, comment, year};
}
