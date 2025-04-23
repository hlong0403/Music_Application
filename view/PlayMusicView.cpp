#include "PlayMusicView.h"
#include <iostream>
#include <cstdlib>

void PlayMusicView :: showLoadSuccess(const string& filepath) {
    cout << "📂 Loading file:: " << filepath << "\n";
}

void PlayMusicView :: showLoadFail(const string& error) {
    cerr << "❌ Failed to load: " << Mix_GetError() << "\n";
}

void PlayMusicView :: showControlMusic(){
    cout << "Controls: [p] Pause, [r] Resume, [n] Next, [b] Back, [+/-] Volume, [q] Quit\n";
}

void PlayMusicView :: showControlMedia(){
    system("clear");
    cout << "🎵 Playing folder as playlist (starting from selected file)\n";
    cout << "Controls: [p] Pause, [r] Resume, [n] Next, [b] Back, [+/-] Volume, [q] Quit\n";
}   