#ifndef _audio_buffer_h_
#define _audio_buffer_h_

#include <string.h>
#include <cstdint>
#include <iostream>
#include <queue>

#define SAMPLE_BUFFER_SIZE 1600

class AudioDataBuffer
{
    public:
        int16_t samples[SAMPLE_BUFFER_SIZE];
        AudioDataBuffer()
        {
            memset(samples, 0, SAMPLE_BUFFER_SIZE * sizeof(int16_t));
        }
};

class AudioBufferAccessor
{
    private:
        AudioDataBuffer ** m_audio_buffers;
        int m_number_audio_buffers;
        // AudioDataBuffer *m_current_buffer;
        int m_buffer_pos;
        int m_buffer_idx;
        int m_total_size;
        std::queue<int>* m_index_queue;

    public:
        AudioBufferAccessor(std::queue<int>* index_queue, AudioDataBuffer **audio_buffers, int number_audio_buffers)
        {
            m_buffer_pos = 0;
            m_buffer_idx = 0;
            m_total_size = number_audio_buffers * SAMPLE_BUFFER_SIZE;
            m_number_audio_buffers = number_audio_buffers;
            m_audio_buffers = audio_buffers;
            m_index_queue = index_queue;
            // m_current_buffer = audio_buffers[0];
        }
      
        void push_index_to_queue(){
            // recycle the queue
            if(m_index_queue->size() >= m_number_audio_buffers){
                m_index_queue->pop();
            }
            m_index_queue->push(m_buffer_idx - 1);
        }

        bool is_queue_empty(){
            return m_index_queue->empty();
        }

        int get_first_index_from_queue(){
            int index = 0;
            if(!m_index_queue->empty()){
                index = m_index_queue->front();
            }
            return index;
        }

        int get_start_position_from_queue()
        {
            int index = 0;
            if(!m_index_queue->empty()){
                index = m_index_queue->front();
            }
            return index * SAMPLE_BUFFER_SIZE ;
        }

        int get_number_audio_buffers(){
            return m_number_audio_buffers;
        }


        int getCurrentPos(){
            return m_buffer_pos;
        }

        int getCurrentIndex(){
            return m_buffer_idx;
        }

        int getIndex()
        {
            return m_buffer_idx * SAMPLE_BUFFER_SIZE + m_buffer_pos;
        }
        void setIndex(int index)
        {
            // handle negative indexes
            index = (index + m_total_size) % m_total_size;
            // work out which buffer
            m_buffer_idx = (index / SAMPLE_BUFFER_SIZE) % m_number_audio_buffers;
            // and where we are in the buffer
            m_buffer_pos = index % SAMPLE_BUFFER_SIZE;
            // m_current_buffer = m_audio_buffers[m_buffer_idx];
        }
        inline int16_t getCurrentSample()
        {
            return m_audio_buffers[m_buffer_idx]->samples[m_buffer_pos];
        }
        inline void setCurrentSample(int16_t sample)
        {
            m_audio_buffers[m_buffer_idx]->samples[m_buffer_pos] = sample;
        }
        inline void rewind(int samples) {
            setIndex(getIndex() - samples);
        }
        inline bool moveToNextSample()
        {
            m_buffer_pos++;
            if (m_buffer_pos == SAMPLE_BUFFER_SIZE)
            {
                m_buffer_pos = 0;
                m_buffer_idx++;
                if (m_buffer_idx == m_number_audio_buffers)
                {
                    m_buffer_idx = 0;
                }
                m_audio_buffers[m_buffer_idx] = m_audio_buffers[m_buffer_idx];
                return true;
            }
            return false;
        }
};

#endif