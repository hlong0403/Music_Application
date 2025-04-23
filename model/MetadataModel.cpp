#include "MetadataModel.h"
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/audioproperties.h>
#include <array>
#include <memory>
#include <cstdio>

MetadataModel:: MetadataModel(){}

bool MetadataModel::readMetadata(const string& filepath,
                                 string& title, string& artist,
                                 string& album, string& genre,
                                 string& comment, unsigned int& year,
                                 int& duration) {
    TagLib::FileRef f(filepath.c_str());

    if (!f.isNull() && f.tag()) {
        TagLib::Tag* tag = f.tag();
        title   = tag->title().to8Bit(true);
        artist  = tag->artist().to8Bit(true);
        album   = tag->album().to8Bit(true);
        genre   = tag->genre().to8Bit(true);
        comment = tag->comment().to8Bit(true);
        year    = tag->year();

        duration = f.audioProperties() ? f.audioProperties()->length() : -1;
        return true;
    }
    return false;
}

bool MetadataModel::writeMetadata(const string& filepath,
                                  const string& title, const string& artist,
                                  const string& album, const string& genre,
                                  const string& comment, unsigned int year) {
    TagLib::FileRef f(filepath.c_str());
    if (!f.isNull() && f.tag()) {
        TagLib::Tag* tag = f.tag();
        tag->setTitle(title);
        tag->setArtist(artist);
        tag->setAlbum(album);
        tag->setGenre(genre);
        tag->setComment(comment);
        tag->setYear(year);
        return f.file()->save();
    }
    return false;
}