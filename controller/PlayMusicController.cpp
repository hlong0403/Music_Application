#include "PlayMusicController.h"
#include "../model/FileBrowser.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <taglib/fileref.h>
#include <taglib/audioproperties.h>
#include <iomanip> // for setw
#include <limits>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "../model/Utils.h"
#include "../S32K144/Board.h"
#include <cstdlib>

using namespace std;

PlayMusicController::PlayMusicController() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "Mix_OpenAudio Error: " << Mix_GetError() << "\n";
    }
}

PlayMusicController::~PlayMusicController() {
    stop();
    Mix_CloseAudio();
    SDL_Quit();
}

void PlayMusicController:: stop(){
    playModel.setStopRequested(true);
    playModel.setPlaying(false);
    Mix_HaltMusic();
    if (playThread.joinable()) {
        playThread.join();
    }
    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
}

void PlayMusicController::start() {
    playModel.setStopRequested(false);
    playModel.setPlaying(true);
    playThread = thread(&PlayMusicController::playbackLoop, this);
}

Mix_Music* PlayMusicController::getMusic() {
    return music;
}

bool PlayMusicController::load(const string& filepath) {
    music = Mix_LoadMUS(filepath.c_str());
    if (!music) {
        return false;
    }
    currentFile = filepath;
    return true;
}

bool PlayMusicController::isPlaying() const {
    return playModel.isPlaying();
}

void PlayMusicController:: playbackLoop(){
    MediaInputReader boardInput("/dev/ttyACM2", 9600);

    PlayMusicController controller;
    vector<string> playlist = playModel.getPlaylist();
    int currentIndex = playModel.getCurrentIndex();
    int volume = 64;

    Mix_VolumeMusic(volume);
    playModel.setSkipToNext(false);
    playModel.setSkipToPrevious(false);

    while (!playModel.isStopRequested()) {
        if (playlist.empty()) break;
        if (currentIndex < 0 || currentIndex >= playlist.size()) currentIndex = 0;

        string file = playlist[currentIndex];
        system("clear");
        cout << "\n▶️ Now playing: " << file << "\n";

        if (FileBrowser::isVideoFile(file)) {
            VideoController vp;
            cout << "[DEBUG] Starting video playback for: " << file << "\n";
        
            vp.playVideo(file);

            if (vp.shouldStop()) {
                playModel.setStopRequested(true);
                break;
            }
        
            if (vp.shouldSkipPrevious()) {
                currentIndex = (currentIndex - 1 + playlist.size()) % playlist.size();
            } else {
                currentIndex = (currentIndex + 1) % playlist.size();
            }
        
            playModel.setCurrentIndex(currentIndex); // Cập nhật chỉ số cho vòng sau
            continue;
        }        
    

        if (!load(file)) {
            playView.showLoadFail( Mix_GetError());
            currentIndex = (currentIndex + 1) % playlist.size();
            continue;
        }

        playView.showLoadSuccess(file);

        // Lấy thời lượng bài hát
        TagLib::FileRef f(file.c_str());
        int totalDuration = 0;
        if (!f.isNull() && f.audioProperties()) {
            totalDuration = f.audioProperties()->length();
        }

        Mix_PlayMusic(music, 1);
        auto start = chrono::steady_clock::now();

        playView.showControlMusic();

        playModel.setSkipToNext(true);

        while (Mix_PlayingMusic() && !playModel.isStopRequested()) {
            //if (!playModel.isPaused()) {
                auto now = chrono::steady_clock::now();
                int elapsed = Mix_GetMusicPosition(music);

                int mins = elapsed / 60, secs = elapsed % 60;
                int totalMins = totalDuration / 60, totalSecs = totalDuration % 60;

                cout << "\r⏱️ "
                          << setfill('0') << setw(2) << mins << ":"
                          << setw(2) << secs << " / "
                          << setw(2) << totalMins << ":"
                          << setw(2) << totalSecs
                          << " 🔉 Volume: " << setw(3) << volume << flush;

                          int c = getCharNonBlocking();
                          string boardCmd = boardInput.listen_once();
                          
                          if (c != EOF) {
                              cout << "\n[DEBUG] Key pressed: '" << (char)c << "'\n";
                          }
                          
                          if (c == 'p' || boardCmd == "T") {
                              if (!Mix_PausedMusic()) {
                                  Mix_PauseMusic();
                                  playModel.setPaused(true);
                                  cout << "\n⏸️ Paused.\n";
                              } else {
                                  Mix_ResumeMusic();
                                  playModel.setPaused(false);
                                  cout << "\n▶️ Resumed.\n";
                              }
                          } else if (c == 'r') {
                              Mix_ResumeMusic();
                              playModel.setPaused(false);
                              cout << "\n▶️ Resumed.\n";
                          } else if (c == 'n' || boardCmd == "N") {
                              playModel.setSkipToNext(true);
                              Mix_HaltMusic();
                              break;
                          } else if (c == 'b' || boardCmd == "P") {
                              playModel.setSkipToPrevious(true);
                              Mix_HaltMusic();
                              break;
                          } else if (c == 's' || boardCmd == "S") {
                              playModel.setStopRequested(true);
                              Mix_HaltMusic();
                              break;
                            } else if (regex_match(boardCmd, regex("^[0-9]+$"))) {
                                int newVolume = stoi(boardCmd);
                                volume = min(128, max(0, newVolume));
                                Mix_VolumeMusic(volume);
                            } else if (c == '+') {
                                volume = min(128, volume + 8);
                                Mix_VolumeMusic(volume);
                            } else if (c == '-') {
                                volume = max(0, volume - 8);
                                Mix_VolumeMusic(volume);
                          } else if (c == 'q') {
                              playModel.setStopRequested(true);
                              Mix_HaltMusic();
                              break;
                          }

                this_thread::sleep_for(chrono::milliseconds(500));
        }

        if (playModel.isStopRequested()) break;

        if (playModel.isSkipToPrevious()) {
            currentIndex = (currentIndex - 1 + playlist.size()) % playlist.size();
            playModel.setSkipToPrevious(false);
        } else if (playModel.isSkipToNext()) {
            currentIndex = (currentIndex + 1) % playlist.size();
            playModel.setSkipToNext(false);
        } else if (!playModel.isPaused() && !playModel.isSkipToPrevious() && !playModel.isSkipToNext()) {
            currentIndex = (currentIndex + 1) % playlist.size();
        }
        
    }

    playModel.setPlaying(false);
    Mix_HaltMusic();
}

void PlayMusicController::runMusic(vector<string> songs) {
    playModel.setPlaylist(songs);
    start();
}

void PlayMusicController :: displayMediaControl(){
    playView.showControlMedia();
}
