#include "Application.h"
#include "controller/MediaListController.h"
#include "controller/MetadataController.h"
#include "controller/PlaylistController.h"
#include "controller/PlayMusicController.h"
#include "controller/VideoMetadataController.h"

#include <iostream>
#include <random>   // cho random_device và mt19937
#include <algorithm> // cho shuffle
#include <cstdlib>

void Application::run() {
    MediaListController mediaCtrl;
    PlaylistController playCtrl;
    MetadataController metaCtrl;
    VideoMetadataController videoMetaCtrl;

    int choice;
    do {
        system("clear");
        cout << "\n====== Home Menu ======\n";
        cout << "1. List media files\n";
        cout << "2. Open playlists\n";
        cout << "3. Exit\n";
        cout << "Select option: ";
        
        
        string buffer;
        getline(cin,buffer);
        if(sscanf(buffer.c_str(), "%d", &choice) != 1) {
            cout << "ERROR: Invalid selection!\n";
            return;
        }

        switch (choice) {
            case 1: 
            {
                vector<string> mediaFiles = mediaCtrl.showMediaList(); 

                bool continueBrowsing = true;
                while (continueBrowsing)
                {
                cout << "\nEnter file number to view metadata (or 0 to return): ";
                int index;
                cin >> index;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (index == 0)
                {
                    continueBrowsing = false;
                    break;
                }

                if (index > 0 && index <= mediaFiles.size()) {
                    string selectedFile = mediaFiles[index - 1];

                    if (FileBrowser::isVideoFile(selectedFile)) {
                        videoMetaCtrl.showVideoMetadata(selectedFile);
                    } else {
                        metaCtrl.showMetadata(selectedFile);

                        cout << "Do you want to edit this metadata? (y/n): ";
                        char metaChoice;
                        cin >> metaChoice;
                        cin.ignore();
                        if (metaChoice == 'y' || metaChoice == 'Y') {
                            metaCtrl.editMetadata(selectedFile);
                        }
                    }

                    cout<< "Do you want to play this media file? (y/n): ";
                    char playChoice;
                    cin >> playChoice;
                    cin.ignore();

                    if (playChoice == 'y' || playChoice == 'Y') {
                        // Tạo sub-playlist bắt đầu từ bài vừa chọn
                        vector<string> subList(mediaFiles.begin() + (index - 1), mediaFiles.end());

                        PlayMusicController mediaPlayCtrl;
                        mediaPlayCtrl.runMusic(subList);

                        mediaPlayCtrl.displayMediaControl();

                        while (mediaPlayCtrl.isPlaying()) {
                            this_thread::sleep_for(chrono::milliseconds(100));
                        }

                        mediaPlayCtrl.stop();
                    }
                }
                }
                break;
            }

            case 2:
            {
                playCtrl.displayPlaylistList();

                cout << "\nEnter playlist number to open or '0' to create new: ";
                int p;
                cin >> p;
                cin.ignore();

                if (p == 0) {
                    playCtrl.addNewPlaylist();
                }

                else if (p > 0 && p <= playCtrl.listPlaylists().size()) {
                    PlaylistModel pl = PlaylistController::loadPlaylist(playCtrl.listPlaylists()[p - 1]);
                    vector<string> songs = pl.getSongs();
                    
                    bool continueBrowsing = true;
                    while (continueBrowsing) {
                        playCtrl.displaySongsInPlaylist(pl.getName(), songs);

                        cout << "\nEnter song number to view metadata (or 0 to continue): ";
                        int songIndex;
                        cin >> songIndex;
                        cin.ignore();

                        if (songIndex == 0) {
                            continueBrowsing = false;
                            break;
                        }

                        if (songIndex > 0 && songIndex <= songs.size()) 
                        {
                            string selectedSong = songs[songIndex - 1];

                            if (FileBrowser::isVideoFile(selectedSong)) {
                                videoMetaCtrl.showVideoMetadata(selectedSong);
                            } else {
                                MetadataController meta;
                                meta.showMetadata(selectedSong);

                                cout << "Do you want to edit this metadata? (y/n): ";
                                char metaChoice;
                                cin >> metaChoice;
                                cin.ignore();

                                if (metaChoice == 'y' || metaChoice == 'Y') {
                                    meta.editMetadata(selectedSong);
                                }
                            }
                        }
                    }

                    playCtrl.deleteSong(pl);
                    playCtrl.addSong(pl);
                
                    cout << "Do you want to play this playlist? (y/n): ";
                    char ch;
                    cin >> ch;
                    cin.ignore();
            
                    if (ch == 'y' || ch == 'Y') {
                        system("clear");
                        cout << "Play this playlist in (1) Order or (2) Shuffle? ";
                        int mode;
                        cin >> mode;
                        cin.ignore();

                        vector<string> songs = pl.getSongs();
                        if (mode == 2) {
                            random_device rd;
                            mt19937 g(rd());
                            shuffle(songs.begin(), songs.end(), g);
                        }

                        PlayMusicController musicCtrl;
                        musicCtrl.runMusic(songs);
                        
                        cout << "🎵 Playing playlist. Controls: p/r/n/b/+/-/q\n";
                        char cmd;
                        do {
                            this_thread::sleep_for(chrono::milliseconds(100));
                        } while (musicCtrl.isPlaying()); // tự dừng khi hết nhạc hoặc bấm q
                    }
                 }
                break;
            }

            case 3:
                cout << "Exiting application.\n";
                break;
            default: cout << "Lựa chọn không hợp lệ!\n";
        }
    } while (choice != 3);
}

