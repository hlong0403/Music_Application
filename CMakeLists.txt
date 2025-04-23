cmake_minimum_required(VERSION 3.10)
project(MediaPlayerCLI)

set(CMAKE_CXX_STANDARD 17)

# === Tìm gói cần thiết ===
find_package(PkgConfig REQUIRED)

# TagLib
pkg_check_modules(TAGLIB REQUIRED taglib)

# SDL2 & SDL2_mixer
find_package(SDL2 REQUIRED)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)

# FFmpeg
pkg_check_modules(AVFORMAT REQUIRED libavformat)
pkg_check_modules(AVCODEC REQUIRED libavcodec)
pkg_check_modules(AVUTIL REQUIRED libavutil)

# === Include path ===
include_directories(
    ${TAGLIB_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${AVFORMAT_INCLUDE_DIRS}
    ${AVCODEC_INCLUDE_DIRS}
    ${AVUTIL_INCLUDE_DIRS}
    include
)

# === Source files ===
add_executable(MediaPlayerCLI
    main.cpp
    Application.cpp

    model/FileBrowser.cpp
    model/MetadataModel.cpp
    model/PlaylistModel.cpp
    model/PlayMusicModel.cpp
    model/Utils.cpp
    model/VideoModel.cpp
    model/VideoMetadataModel.cpp

    view/MediaListView.cpp
    view/MetadataView.cpp
    view/PlaylistView.cpp
    view/PlayMusicView.cpp
    view/VideoView.cpp
    view/VideoMetadataView.cpp

    controller/MediaListController.cpp
    controller/MetadataController.cpp
    controller/PlaylistController.cpp
    controller/PlayMusicController.cpp
    controller/VideoController.cpp
    controller/VideoMetadataController.cpp

    S32K144/Board.cpp
)

# === Link thư viện ===
target_link_libraries(MediaPlayerCLI
    ${TAGLIB_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${AVFORMAT_LIBRARIES}
    ${AVCODEC_LIBRARIES}
    ${AVUTIL_LIBRARIES}

)
