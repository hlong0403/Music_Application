#ifndef METADATA_CONTROLLER_H
#define METADATA_CONTROLLER_H

#include "../model/MetadataModel.h"
#include "../view/MetadataView.h"

#include <string>
using namespace std;

class MetadataController {
    private:
        MetadataModel model;
        MetadataView view;

    public:
        void showMetadata(const string& filepath);
        void editMetadata(const string& filepath);
};

#endif
