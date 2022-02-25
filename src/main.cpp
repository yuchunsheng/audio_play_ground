#include <iostream>

#include "read_wav.h"

int main(int, char**) {
    std::cout << "Hello, world!\n";
    int result = read_wav_ifstream("/home/ycsheng/disk3T/temp/output1.wav");
    // int result = read_wav_file("/home/ycsheng/disk3T/temp/output1.wav");
}
