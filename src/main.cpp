#include <iostream>

#include "read_wav.h"
#include "AudioBufferAccessor.h"
#include "hello_world_test.h"

#define AUDIO_BUFFER_COUNT 11  //abut 1 seconds (1600 * 10 )


int main(int, char**) {
    std::cout << "Hello, world!\n";

    AudioBufferAccessor * write_ring_buffer_accessor=new AudioBufferAccessor(AUDIO_BUFFER_COUNT);

    std::cout << write_ring_buffer_accessor << " buffer pointer from main" << std::endl;

    int result = read_wav_2_audiobuffer("/home/ycsheng/disk3T/audio_datasets/speech_commands/test/yes/fa446c16_nohash_0.wav", write_ring_buffer_accessor);

    
    write_ring_buffer_accessor->delete_audioBuffers();
    delete(write_ring_buffer_accessor);
    
    // int result = read_wav_ifstream("/home/ycsheng/disk3T/temp/output1.wav");
    // int reulst = read_wav_ifstream("/home/ycsheng/disk3T/audio_datasets/speech_commands/test/yes/fa446c16_nohash_0.wav");
    // int result = read_wav_file("/home/ycsheng/disk3T/temp/output1.wav");
    // int result = read_wav_header("/home/ycsheng/disk3T/temp/file_example_WAV_1MG.wav");
    // AudioBuffer *m_audio_buffers[AUDIO_BUFFER_COUNT];
    // for (int i = 0; i < AUDIO_BUFFER_COUNT; i++)
    // {
    //     m_audio_buffers[i] = new AudioBuffer();
    // }
    
    // RingBufferAccessor *reader = new RingBufferAccessor(m_audio_buffers, AUDIO_BUFFER_COUNT);
    // RingBufferAccessor *m_write_ring_buffer_accessor = new RingBufferAccessor(m_audio_buffers, AUDIO_BUFFER_COUNT);

    // reader->setIndex(m_write_ring_buffer_accessor->getIndex());

    // delete reader;
    // delete m_write_ring_buffer_accessor;
    
    
    // run_hello_world_test();
    return 0;
}
