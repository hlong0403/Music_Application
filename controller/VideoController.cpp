#include "VideoController.h"
#include "../model/Utils.h"
#include "../S32K144/Board.h"
#include <thread>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <iomanip>


VideoController::VideoController() 
: stopRequested(false), skipToNext(false), skipToPrevious(false), done(false), volume(64) {}

void VideoController::playVideo(const string& file) {
    MediaInputReader boardInput("/dev/ttyACM2", 9600);
    
    vp.play(file, volume);
    view.showControls();

    thread controlThread([&]() 
    {
        view.notifyThreadStart();

        
        while (vp.isRunning() && !stopRequested && !done) {

            // vp.setPaused(true);

            int elapsed = vp.getElapsedSeconds();   // bạn cần cài đặt
            int totalDuration = vp.getTotalDuration(file); // bạn cần cài đặt

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
                view.displayKeyPressed(c);
            }

            // Điều khiển từ bàn phím
            if (c == 'p') {
                vp.pause();
            } else if (c == 'r') {
                vp.resume();
            } else if (c == 'n') {
                skipToNext = true;
                vp.stop();
                done = true;
                break;
            } else if (c == 'b') {
                skipToPrevious = true;
                vp.stop();
                done = true;
                break;
            } else if (c == '+') {
                volume = min(128, volume + 8);
                vp.stop();
                vp.play(file, volume);
            } else if (c == '-') {
                volume = max(0, volume - 8);
                vp.stop();
                vp.play(file, volume);
            } else if (c == 'q') {
                stopRequested = true;
                vp.stop();
                done = true;
                break;
            }

            // Điều khiển từ board
            if (boardCmd == "T") {
                if (vp.isPaused()) {
                    vp.resume();
                } else {
                    vp.pause();
                }
            } else if (boardCmd == "N") {
                skipToNext = true;
                vp.stop();
                done = true;
                break;
            } else if (boardCmd == "P") {
                skipToPrevious = true;
                vp.stop();
                done = true;
                break;
            } else if (boardCmd == "S") {
                stopRequested = true;
                vp.stop();
                done = true;
                break;
            } else if (regex_match(boardCmd, regex("^[0-9]+$"))) {
                int newVolume = min(128, max(0, stoi(boardCmd)));
                volume = newVolume;
                vp.stop();
                vp.play(file, volume);
            }

            this_thread::sleep_for(chrono::milliseconds(100));
        }
    });

    while (vp.isRunning() && !done) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    if (controlThread.joinable()) controlThread.join();
}

bool VideoController::shouldStop() const { return stopRequested; }
bool VideoController::shouldSkipNext() const { return skipToNext; }
bool VideoController::shouldSkipPrevious() const { return skipToPrevious; }
