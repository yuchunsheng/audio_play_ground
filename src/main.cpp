#include <iostream>

#include "read_wav.h"
#include "RingBuffer.h"

#define AUDIO_BUFFER_COUNT 11

int main(int, char**) {
    std::cout << "Hello, world!\n";
    // int result = read_wav_ifstream("/home/ycsheng/disk3T/temp/output1.wav");
    // int result = read_wav_file("/home/ycsheng/disk3T/temp/output1.wav");
    // int result = read_wav_header("/home/ycsheng/disk3T/temp/file_example_WAV_1MG.wav");
    AudioBuffer *m_audio_buffers[AUDIO_BUFFER_COUNT];
    for (int i = 0; i < AUDIO_BUFFER_COUNT; i++)
    {
        m_audio_buffers[i] = new AudioBuffer();
    }
    
    RingBufferAccessor *reader = new RingBufferAccessor(m_audio_buffers, AUDIO_BUFFER_COUNT);
    RingBufferAccessor *m_write_ring_buffer_accessor = new RingBufferAccessor(m_audio_buffers, AUDIO_BUFFER_COUNT);

    reader->setIndex(m_write_ring_buffer_accessor->getIndex());

    delete reader;
    delete m_write_ring_buffer_accessor;
    delete[] m_audio_buffers;
}
