extern "C" {
    #include <libavformat/avformat.h>
    #include <libavutil/dict.h>
    #include <libavutil/time.h>
    }
    
#include "VideoMetadataModel.h"
#include <iostream>

VideoMetadataModel::VideoMetadataModel() {
}

bool VideoMetadataModel::readMetadata(const string& filepath,
                                        string& title, string& artist,
                                        string& album, string& genre,
                                        string& comment, string& year,
                                        string& codec_name, int& width, int& height,
                                        double& duration_seconds) 
{
    AVFormatContext* fmt_ctx = nullptr;

    if (avformat_open_input(&fmt_ctx, filepath.c_str(), nullptr, nullptr) != 0) {
        //cerr << "Không thể mở file video\n";
        return false;
    }

    if (avformat_find_stream_info(fmt_ctx, nullptr) < 0) {
        //cerr << "Không thể đọc thông tin stream\n";
        avformat_close_input(&fmt_ctx);
        return false;
    }

    // ==== Metadata chung ====
    AVDictionary* metadata = fmt_ctx->metadata;

    auto getTag = [&](const char* key) -> string {
        AVDictionaryEntry* entry = av_dict_get(metadata, key, nullptr, 0);
        return entry ? entry->value : "";
    };

    title   = getTag("title");
    artist  = getTag("artist");
    album   = getTag("album");
    genre   = getTag("genre");
    comment = getTag("comment");
    year    = getTag("date");

    // ==== Thông tin kỹ thuật ====
    int video_stream_index = -1;
    for (unsigned int i = 0; i < fmt_ctx->nb_streams; ++i) {
        if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            video_stream_index = i;
            break;
        }
    }

    if (video_stream_index != -1) {
        AVStream* video_stream = fmt_ctx->streams[video_stream_index];
        AVCodecParameters* codecpar = video_stream->codecpar;

        const AVCodec* codec = avcodec_find_decoder(codecpar->codec_id);
        codec_name = codec ? codec->name : "unknown";

        width  = codecpar->width;
        height = codecpar->height;

        if (video_stream->duration != AV_NOPTS_VALUE && video_stream->time_base.den != 0) {
            duration_seconds = video_stream->duration * av_q2d(video_stream->time_base);
        } else {
            duration_seconds = fmt_ctx->duration / (double)AV_TIME_BASE;
        }
    } else {
        codec_name = "unknown";
        width = height = 0;
        duration_seconds = fmt_ctx->duration / (double)AV_TIME_BASE;
    }

    avformat_close_input(&fmt_ctx);
    return true;
}