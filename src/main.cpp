#include <iostream>

#include "read_wav.h"
#include "AudioBufferAccessor.h"
#include "AudioDataProcessor.h"
#include "hello_world_test.h"

#define WINDOW_SIZE 320
#define STEP_SIZE 160
#define POOLING_SIZE 6
#define AUDIO_LENGTH 16000

//  SAMPLE_BUFFER_SIZE 1600

#define AUDIO_BUFFER_COUNT 11  //abut 1 seconds (1600 * 10 )


int main(int, char**) {
    std::cout << "Hello, world!\n";
    AudioDataBuffer ** audio_buffers;
    audio_buffers = new AudioDataBuffer *[AUDIO_BUFFER_COUNT];
    std::queue<int> index_queue ;

    AudioDataProcessor* audio_processor = new AudioDataProcessor(AUDIO_LENGTH, WINDOW_SIZE, STEP_SIZE, POOLING_SIZE);

    // allocate the audio buffers
    for (int i = 0; i < AUDIO_BUFFER_COUNT; i++)
    {
        audio_buffers[i] = new AudioDataBuffer();
    }

    AudioBufferAccessor * write_buffer_accessor=new AudioBufferAccessor(&index_queue, audio_buffers, AUDIO_BUFFER_COUNT);
    AudioBufferAccessor * read_buffer_accessor=new AudioBufferAccessor(&index_queue, audio_buffers, AUDIO_BUFFER_COUNT);

    std::cout << write_buffer_accessor << " buffer pointer from main" << std::endl;

    int result = read_wav_2_audiobuffer("/home/ycsheng/disk3T/audio_datasets/speech_commands/test/yes/fa446c16_nohash_0.wav", write_buffer_accessor);
    
    float  temp[43*98];

    if(index_queue.size()>= 9){
        // std::cout << "the queue is full" << std::endl;
        audio_processor->get_spectrogram(read_buffer_accessor, temp);
    }

    // while (!write_buffer_accessor->is_queue_empty())
    // {
    //     int index = write_buffer_accessor->get_index_from_queue();
    //     std::cout << index << " is the current index" << std::endl;
    // }
    

    for (int i = 0; i < AUDIO_BUFFER_COUNT; i++)
    {
        delete(audio_buffers[i]);
    }
    delete[] audio_buffers;

    delete(write_buffer_accessor);
    
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
