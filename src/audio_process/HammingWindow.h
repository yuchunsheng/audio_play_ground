#ifndef HAMMING_H
#define HAMMING_H

#include <inttypes.h>

class HammingWindow
{
private:
    float *m_coefficients;
    int m_window_size;

public:
    HammingWindow(int window_size);
    ~HammingWindow();
    void applyWindow(float *input);
};

#endif