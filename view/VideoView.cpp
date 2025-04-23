#include "VideoView.h"

void VideoView :: showControls() {
    std::cout << "🎬 Video playing in separate window.\n";
    std::cout << "Controls: [p] Pause, [r] Resume, [n] Next, [b] Back, [+/-] Volume, [q] Quit\n";
}

void VideoView :: notifyThreadStart() {
    std::cout << "\n🧵 controlThread STARTED\n";
}

void VideoView :: displayKeyPressed(char c) {
    std::cout << "\n🔹 Key Pressed: " << c << "\n";
}
