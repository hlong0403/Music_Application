#include "VideoModel.h"
#include <iostream>
#include <csignal>
#include <sys/types.h>
#include <unistd.h>
#include <spawn.h>
#include <cstring>
#include <sys/wait.h>
#include <fcntl.h>
#include <cmath> // thư viện làm tròn

VideoModel::VideoModel() : running(false), pid(-1) {}
VideoModel::~VideoModel() {
    stop();
}

void VideoModel::playProcess(const string& filepath, int volume) {
    string volumeStr = to_string(volume);
    running = true;
    const char* argv[] = {
        "ffplay",
        "-autoexit",
        "-loglevel", "quiet",
        "-volume", volumeStr.c_str(),
        filepath.c_str(),
        nullptr
    };

    pid_t child_pid;
    posix_spawn_file_actions_t actions;
    posix_spawn_file_actions_init(&actions);

    // ❗ Redirect stdin của ffplay sang /dev/null để không chiếm terminal
    // posix_spawn_file_actions_addopen(&actions, 0, "/dev/null", O_RDONLY, 0);

    if (posix_spawnp(&child_pid, "ffplay", &actions, nullptr, (char* const*)argv, environ) == 0) {
        pid = child_pid;
        
        waitpid(pid, nullptr, 0);
        running = false;
    } else {
        cerr << "❌ Failed to launch ffplay\n";
        running = false;
    }

    posix_spawn_file_actions_destroy(&actions);
}

void VideoModel::play(const string& filepath, int volume) {
    running = true;
    elapsedBeforePause = 0;
    paused = false;
    startTime = std::chrono::steady_clock::now();
    stop(); // đảm bảo không có ffplay nào đang chạy
    playThread = thread(&VideoModel::playProcess, this, filepath, volume);
}

void VideoModel::stop() {
    if (running && pid > 0) {
        kill(pid, SIGKILL);
        running = false;
    }
    if (playThread.joinable()) playThread.join();
}

void VideoModel::pause() {
    if (running && (pid > 0 && !paused)) {
        cout << "\n⏸ Pausing video (pid: " << pid << ")\n";
        paused = true;
        pauseTime = std::chrono::steady_clock::now();
        elapsedBeforePause += std::chrono::duration_cast<std::chrono::seconds>(pauseTime - startTime).count();
        kill(pid, SIGSTOP);
    }
}

void VideoModel::resume() {
    if (running && (pid > 0 && paused)) {
        cout << "\n▶️ Resuming video (pid: " << pid << ")\n";
        paused = false;
        startTime = std::chrono::steady_clock::now(); // đánh dấu lại thời gian bắt đầu để tiếp tục đếm
        kill(pid, SIGCONT);
    }
}
bool VideoModel::isRunning() const {
    return running;
}

int VideoModel::getElapsedSeconds() {
    if (!running) return 0;
    if (paused) {
        return elapsedBeforePause;
    } else {
        auto now = std::chrono::steady_clock::now();
        return elapsedBeforePause + std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    }
}

int VideoModel::getTotalDuration(const string& filepath) {
    string title, artist, album, genre, comment, year, codec_name;
    int width, height;
    double duration_seconds;

    if (metadata.readMetadata(filepath, title, artist, album, genre, comment, year, codec_name, width, height, duration_seconds)) {
        return static_cast<int>(ceil(duration_seconds));
    } else {
        cout << "Cannot read metadata from file: " << filepath << "\n";
        return 0;
    }
}

bool VideoModel::isPaused() const {
    return paused;
}