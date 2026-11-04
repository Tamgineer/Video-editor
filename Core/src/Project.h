#pragma once
#include <fstream>
#include <filesystem>
#include "NotImplemented.h"

extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/imgutils.h>
    #include <libavutil/opt.h>
}

#include "ITrack.h"
class Project {
public:
	std::string Name{};
	int FPS{};
	int TotalFrames{75}; //we might need to calculate this
	int WIDTH{};
	int HEIGHT{};
	std::string Filepath;
    std::fstream ProjectFile;
	//mediapool
	//timeline

	//Let's pretend that the fstream is our video output for the time being.

	//if the project already exists somewhere
	Project(std::string path) : Filepath(path) {
		Load(path);
	}

	//Otherwise
	Project(int width, int height) : WIDTH(width), HEIGHT(height) {

	}

    /*
        NB: I know this section of code is AI generated, but this is only being used as a proof
        of concept that the libraries work
    */
	const int Render(std::string output) {
        // 1. Initialize Output Format Context for MP4
        AVFormatContext* fmt_ctx = nullptr;
        avformat_alloc_output_context2(&fmt_ctx, nullptr, nullptr, output.c_str());
        if (!fmt_ctx) {
            std::cerr << "Could not allocate output format context\n";
            return -1;
        }

        // 2. Find the H.264 Encoder
        const AVCodec* codec = avcodec_find_encoder_by_name("libx264");
        if (!codec) {
            std::cerr << "Codec 'libx264' not found\n";
            return -1;
        }

        AVStream* stream = avformat_new_stream(fmt_ctx, nullptr);
        if (!stream) {
            std::cerr << "Could not allocate stream\n";
            return -1;
        }

        AVCodecContext* codec_ctx = avcodec_alloc_context3(codec);
        if (!codec_ctx) {
            std::cerr << "Could not allocate codec context\n";
            return -1;
        }

        // Configure encoder parameters
        codec_ctx->width = WIDTH;
        codec_ctx->height = HEIGHT;
        codec_ctx->time_base = { 1, FPS };
        codec_ctx->framerate = { FPS, 1 };
        codec_ctx->gop_size = 12;       // Emit I-frame every 12 frames
        codec_ctx->max_b_frames = 1;
        codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P; // Standard format for H.264

        if (fmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
            codec_ctx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

        // Open the encoder
        if (avcodec_open2(codec_ctx, codec, nullptr) < 0) {
            std::cerr << "Could not open codec\n";
            return -1;
        }

        // Link codec parameters to the output stream
        avcodec_parameters_from_context(stream->codecpar, codec_ctx);
        stream->time_base = codec_ctx->time_base;

        // Open the output file handle
        if (!(fmt_ctx->oformat->flags & AVFMT_NOFILE)) {
            if (avio_open(&fmt_ctx->pb, output.c_str(), AVIO_FLAG_WRITE) < 0) {
                std::cerr << "Could not open output file " << output.c_str() << "\n";
                return -1;
            }
        }

        // Write container header
        if (avformat_write_header(fmt_ctx, nullptr) < 0) {
            std::cerr << "Error writing header\n";
            return -1;
        }

        // 3. Allocate Frame and Packet buffers
        AVFrame* frame = av_frame_alloc();
        frame->format = codec_ctx->pix_fmt;
        frame->width = codec_ctx->width;
        frame->height = codec_ctx->height;
        if (av_frame_get_buffer(frame, 32) < 0) {
            std::cerr << "Could not allocate frame data buffer\n";
            return -1;
        }

        AVPacket* pkt = av_packet_alloc();

        // Helper lambda to handle encoding and multiplexing packets
        auto encode_and_write = [&](AVFrame* f) {
            int ret = avcodec_send_frame(codec_ctx, f);
            if (ret < 0) return;

            while (ret >= 0) {
                ret = avcodec_receive_packet(codec_ctx, pkt);
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                    break;
                }
                else if (ret < 0) {
                    std::cerr << "Error during encoding\n";
                    break;
                }

                av_packet_rescale_ts(pkt, codec_ctx->time_base, stream->time_base);
                pkt->stream_index = stream->index;
                av_interleaved_write_frame(fmt_ctx, pkt);
                av_packet_unref(pkt);
            }
            };

        // 4. Main Frame Generation & Encoding Loop
        for (int i = 0; i < TotalFrames; i++) {
            if (av_frame_make_writable(frame) < 0) break;

            // Generate a synthetic moving grayscale pattern (Y plane)
            for (int y = 0; y < HEIGHT; y++) {
                for (int x = 0; x < WIDTH; x++) {
                    frame->data[0][y * frame->linesize[0] + x] = (x + y + i * 10) & 255;
                }
            }
            // Set U and V planes to 128 (neutral gray / no color)
            for (int y = 0; y < HEIGHT / 2; y++) {
                for (int x = 0; x < WIDTH / 2; x++) {
                    frame->data[1][y * frame->linesize[1] + x] = 128; // U
                    frame->data[2][y * frame->linesize[2] + x] = 128; // V
                }
            }

            frame->pts = i; // Presentation timestamp
            encode_and_write(frame);
        }

        // 5. Flush remaining delayed frames from the encoder
        encode_and_write(nullptr);

        // 6. Finalize and Clean Up
        av_write_trailer(fmt_ctx);

        av_frame_free(&frame);
        av_packet_free(&pkt);
        avcodec_free_context(&codec_ctx);
        if (!(fmt_ctx->oformat->flags & AVFMT_NOFILE))
            avio_closep(&fmt_ctx->pb);
        avformat_free_context(fmt_ctx);

        std::cout << "Success! Video saved as " << output << "\n";
        return 0;
	}

	int Save() {
        if (Filepath == "") {
            std::cerr << "Filepath not specified";
            return 1;
        }
        std::string p = Filepath + Name + ".tc";

        //I don't know if making a project file if it doesn't exist
        //is a good responsibility for the save function, or if we
        //should give the responsibility to the editor?
        if (!std::filesystem::exists(p)) {
            std::cerr << "Filepath doesn't exist, making a new file...\n";
            std::ofstream temp{ p };
            temp.close();
            //return -1;
        }

        ProjectFile = std::fstream{ p , std::ios::in | std::ios::out};

        if (!ProjectFile) {
            std::cerr << "Filepath could not be used for writing\n";
            return 1;
        }

        ProjectFile << "Version=0.1\n";
        ProjectFile << "name="    << Name   << "\n";
        ProjectFile << "Width="  << WIDTH  << "\n";
        ProjectFile << "Height=" << HEIGHT << "\n";
        ProjectFile << "FPS="    << FPS    << "\n";

	}

    void SetFilepath(std::string path) {
        Filepath = path;
    }

    void SetName(std::string name) {
        Name = name;
    }

	void SetFPS(int fps) {
		FPS = { fps };
	}

    void PrintProperties() {
        std::cout << Name << "\n"
            << " width:  " << WIDTH << "\n"
            << " height: " << HEIGHT << "\n"
            << " fps:    " << FPS << "\n"
        ;
    }
private:
	//TODO: return error codes
	int Load(std::string path) {
        ProjectFile = std::fstream{path, std::ios::in | std::ios::out};

        if (!ProjectFile) {
            std::cerr << "Project file could not be opened!\n";
            return 1;
        }
        std::string str{};
        while (std::getline(ProjectFile, str))
            Interperate(str);

        return 0;
    }

    void Interperate(std::string str) {
        auto index = str.find("=");
        std::string s{ str.substr(0, index) };
        std::string t{ str.substr(index + 1, str.length()) };
        if (s == "name") {
            Name = t;
        }

        if (s == "width") {
            WIDTH = std::stoi(t);
        }

        if (s == "height") {
            WIDTH = std::stoi(t);
        }

        if (s == "fps") {
            WIDTH = std::stoi(t);
        }
    }
};