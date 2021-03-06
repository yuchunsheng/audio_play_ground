#ifndef READ_WAV_H
#define READ_WAV_H

#include <cstdint>
#include <fstream>
#include<vector>
#include<iostream>
#include "AudioBufferAccessor.h"

typedef struct  WAV_HEADER
{
    /* RIFF Chunk Descriptor */
    uint8_t         RIFF[4];        // RIFF Header Magic header
    uint32_t        ChunkSize;      // RIFF Chunk Size
    uint8_t         WAVE[4];        // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t         fmt[4];         // FMT header
    uint32_t        Subchunk1Size;  // Size of the fmt chunk
    uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t        NumOfChan;      // Number of channels 1=Mono 2=Sterio
    uint32_t        SamplesPerSec;  // Sampling Frequency in Hz
    uint32_t        bytesPerSec;    // bytes per second
    uint16_t        blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    uint16_t        bitsPerSample;  // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t         Subchunk2ID[4]; // "data"  string
    uint32_t        Subchunk2Size;  // Sampled data length
} wav_hdr;

std::string get_audio_format(uint16_t input);
// Function prototypes
int getFileSize(FILE* inFile);

int read_wav_file(const char* filePath);

int read_wav_ifstream(std::string file_path);


int read_wav_header(std::string file_path);

int read_wav_2_audiobuffer(std::string file_path,  AudioBufferAccessor * write_ring_buffer_accessor);

#endif