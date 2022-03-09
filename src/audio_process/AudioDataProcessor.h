#ifndef AUDIO_DATA_PROCESSOR_H
#define AUDIO_DATA_PROCESSOR_H

#include <stdlib.h>
#include <stdint.h>
// #define FIXED_POINT (16)
#include "kiss_fftr.h"

#include "AudioBufferAccessor.h"
#include "HammingWindow.h"

class AudioDataProcessor
{
private:
    int m_audio_length;
    int m_window_size;
    int m_step_size;
    int m_pooling_size;
    size_t m_fft_size;
    float *m_fft_input;
    int m_energy_size;
    int m_pooled_energy_size;
    float *m_energy;
    kiss_fft_cpx *m_fft_output;
    kiss_fftr_cfg m_cfg;

    HammingWindow *m_hamming_window;

    void get_spectrogram_segment(float *output_spectrogram_row);

public:
    AudioDataProcessor(int audio_length, int window_size, int step_size, int pooling_size);
    ~AudioDataProcessor();
    void get_spectrogram(AudioBufferAccessor *reader, float *output_spectrogram);
};

#endif