#include <iostream>
#include <string>
#include <algorithm>

#include "read_wav.h"
// #include "AudioFile.h"


using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;




std::string get_audio_format(uint16_t input){
    std::string result ;
    switch(input){
        case(1):
            result = "PCM";
            break;
        case(3):
            result = "IEEE float";
            break;
        default:
            result = "others";
            break;
    }

    return result;
}

void add_sample(int16_t sample, AudioBufferAccessor *write_ring_buffer_accessor)
{
    // std::cout << write_ring_buffer_accessor << " buffer pointer in addSample" << std::endl;
    // store the sample
    write_ring_buffer_accessor->setCurrentSample(sample);
    if (write_ring_buffer_accessor->moveToNextSample())
    {
        // trigger the processor task as we've filled a buffer
        // std::cout << write_ring_buffer_accessor->getCurrentPos()<<" is the current pos" << std::endl;
        // std::cout << write_ring_buffer_accessor->getCurrentIndex()<<" is the current index" << std::endl;
        // if reach the bottome then rewind
        
        // std::cout << temp << " the current index" << std::endl;
        write_ring_buffer_accessor->push_index_to_queue();
    }
}

int read_wav_2_audiobuffer(string file_path, AudioBufferAccessor * write_ring_buffer_accessor){
    wav_hdr wav_header;
    int headerSize = sizeof(wav_hdr), filelength = 0;
    std::ifstream wav_stream(file_path, std::ifstream::binary | std::ifstream::in);
    if(wav_stream.good()){
        wav_stream.read(reinterpret_cast<char*>(&wav_header), headerSize );
        std::cout << "AudioFormat: " <<get_audio_format(wav_header.AudioFormat) << std::endl;
        std::cout << "NumOfChan: " <<wav_header.NumOfChan << std::endl;
        std::cout << "SamplesPerSec: " <<wav_header.SamplesPerSec << std::endl;
        std::cout << "bytesPerSec: " <<wav_header.bytesPerSec << std::endl;
        std::cout << "Subchunk2ID="<< wav_header.Subchunk2ID << std::endl;
        std::cout << "Subchunk2Size=" << wav_header.Subchunk2Size << std::endl;

        if((get_audio_format(wav_header.AudioFormat) == "PCM") && (wav_header.NumOfChan == 1)){
            int byte_length =  wav_header.bytesPerSec/wav_header.SamplesPerSec;
            if(byte_length == 2){
                int data_length = (wav_header.Subchunk2Size/byte_length);
                int16_t*  wav_data = new int16_t[data_length];      
                wav_stream.read(reinterpret_cast<char*>(wav_data),wav_header.Subchunk2Size);
                std::cout << write_ring_buffer_accessor << " buffer pointer" << std::endl;
                // add_sample(wav_data[0], write_ring_buffer_accessor);
                for(int i = 0 ; i <= data_length; i++){
                   add_sample(wav_data[i], write_ring_buffer_accessor);
                }

                delete[] wav_data;
                std::cout << "good, no issues" << std::endl;
            }
        }else{
            std::cout << "wav format is not compatble." << std::endl;
        }
    }
    return 0;
}
int read_wav_header(string file_path){
    wav_hdr wav_header;
    int headerSize = sizeof(wav_hdr), filelength = 0;
    std::cout << "RIFF size:" << sizeof(wav_header.RIFF) << std::endl;

    std::ifstream wav_stream(file_path, std::ifstream::binary | std::ifstream::in);

    if(wav_stream.good()){
        wav_stream.read(reinterpret_cast<char*>(&wav_header), headerSize );
        std::streamsize bytes = wav_stream.gcount();

        std::cout << "Read: d=" << wav_header.RIFF  << std::endl; 
        std::cout<< "chunksize =" << wav_header.ChunkSize << std::endl;
        std::cout << "AudioFormat: " <<get_audio_format(wav_header.AudioFormat) << std::endl;
        std::cout << "NumOfChan: " <<wav_header.NumOfChan << std::endl;
        std::cout << "SamplesPerSec: " <<wav_header.SamplesPerSec << std::endl;
        std::cout << "bytesPerSec: " <<wav_header.bytesPerSec << std::endl;
        std::cout << "blockAlign: " <<wav_header.blockAlign << std::endl;

        std::cout << "Subchunk2ID="<< wav_header.Subchunk2ID << std::endl;
        std::cout << "Subchunk2Size=" << wav_header.Subchunk2Size << std::endl;

        std::cout << "bytes read: " << bytes << std::endl;

        int current_position = wav_stream.tellg();
        std::cout << "current position " << current_position << std::endl;

    }
    wav_stream.close();
    return 0;

}

int read_wav_ifstream(string file_path){
    wav_hdr wav_header;
    int headerSize = sizeof(wav_hdr), filelength = 0;
    std::cout << "RIFF size:" << sizeof(wav_header.RIFF) << std::endl;

    std::ifstream wav_stream(file_path, std::ifstream::binary | std::ifstream::in);

    if(wav_stream.good()){
        wav_stream.read(reinterpret_cast<char*>(&wav_header), headerSize );
        std::streamsize bytes = wav_stream.gcount();

        std::cout << "Read: d=" << wav_header.RIFF  << std::endl; 
        std::cout<< "chunksize =" << wav_header.ChunkSize << std::endl;
        std::cout << "AudioFormat: " <<get_audio_format(wav_header.AudioFormat)<< std::endl;
        std::cout << "NumOfChan: " <<wav_header.NumOfChan << std::endl;
        std::cout << "SamplesPerSec: " <<wav_header.SamplesPerSec << std::endl;
        std::cout << "bytesPerSec: " <<wav_header.bytesPerSec << std::endl;
        std::cout << "Subchunk2ID="<< wav_header.Subchunk2ID << std::endl;
        std::cout << "Subchunk2Size=" << wav_header.Subchunk2Size << std::endl;

        std::cout << "bytes read: " << bytes << std::endl;

        int current_position = wav_stream.tellg();
        std::cout << "current position " << current_position << std::endl;

        int16_t*  wav_data = new int16_t[(wav_header.Subchunk2Size/sizeof(uint16_t))];
        
        wav_stream.read(reinterpret_cast<char*>(wav_data),wav_header.Subchunk2Size);

        std::cout << "value: " << wav_data[155] << std::endl;

        std::cout << "value: " << wav_data[200] << std::endl;

        std::cout << "max = " << *std::max_element(wav_data, wav_data+(wav_header.Subchunk2Size/sizeof(uint16_t))) << std::endl;
        std::cout << "max = " << *std::min_element(wav_data, wav_data+(wav_header.Subchunk2Size/sizeof(uint16_t))) << std::endl;

        delete[] wav_data;

    }
    
    wav_stream.close();
    return 0;
}

// find the file size
int getFileSize(FILE* inFile)
{
    int fileSize = 0;
    fseek(inFile, 0, SEEK_END);

    fileSize = ftell(inFile);

    fseek(inFile, 0, SEEK_SET);
    return fileSize;
}

int read_wav_file(const char* filePath){
    wav_hdr wavHeader;
    int headerSize = sizeof(wav_hdr), filelength = 0;

    // const char* filePath = "/home/ycsheng/disk3T/";
    
    FILE* wavFile = fopen(filePath, "r");
    if (wavFile == nullptr)
    {
        fprintf(stderr, "Unable to open wave file: %s\n", filePath);
        return 1;
    }

    //Read the header
    size_t bytesRead = fread(&wavHeader, 1, headerSize, wavFile);
    cout << "Header Read " << bytesRead << " bytes." << endl;
    if (bytesRead > 0)
    {
        //Read the data
        uint16_t bytesPerSample = wavHeader.bitsPerSample / 8;      //Number     of bytes per sample
        uint64_t numSamples = wavHeader.ChunkSize / bytesPerSample; //How many samples are in the wav file?
        static const uint16_t BUFFER_SIZE = 4096;
        int8_t* buffer = new int8_t[BUFFER_SIZE];
        while ((bytesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE / (sizeof buffer[0]), wavFile)) > 0)
        {
            /** DO SOMETHING WITH THE WAVE DATA HERE **/
            cout << "Read " << bytesRead << " bytes." << endl;
        }
        delete [] buffer;
        buffer = nullptr;
        filelength = getFileSize(wavFile);

        cout << "File is                    :" << filelength << " bytes." << endl;
        cout << "RIFF header                :" << wavHeader.RIFF[0] << wavHeader.RIFF[1] << wavHeader.RIFF[2] << wavHeader.RIFF[3] << endl;
        cout << "WAVE header                :" << wavHeader.WAVE[0] << wavHeader.WAVE[1] << wavHeader.WAVE[2] << wavHeader.WAVE[3] << endl;
        cout << "FMT                        :" << wavHeader.fmt[0] << wavHeader.fmt[1] << wavHeader.fmt[2] << wavHeader.fmt[3] << endl;
        cout << "Data size                  :" << wavHeader.ChunkSize << endl;

        // Display the sampling Rate from the header
        cout << "Sampling Rate              :" << wavHeader.SamplesPerSec << endl;
        cout << "Number of bits used        :" << wavHeader.bitsPerSample << endl;
        cout << "Number of channels         :" << wavHeader.NumOfChan << endl;
        cout << "Number of bytes per second :" << wavHeader.bytesPerSec << endl;
        cout << "Data length                :" << wavHeader.Subchunk2Size << endl;
        cout << "Audio Format               :" << wavHeader.AudioFormat << endl;
        // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM

        cout << "Block align                :" << wavHeader.blockAlign << endl;
        cout << "Data string                :" << wavHeader.Subchunk2ID[0] << wavHeader.Subchunk2ID[1] << wavHeader.Subchunk2ID[2] << wavHeader.Subchunk2ID[3] << endl;
    }
    fclose(wavFile);
    return 0;
}