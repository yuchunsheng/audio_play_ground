#ifndef mobilenet_h
#define mobilenet_h

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"


class Mobilenet{
    private:
        tflite::ErrorReporter *m_error_reporter;

        tflite::MicroMutableOpResolver<10> *m_resolver;
        
        const tflite::Model *m_model;
        tflite::MicroInterpreter *m_interpreter;
        TfLiteTensor *input;
        TfLiteTensor *output;
        uint8_t *m_tensor_arena;

    public:
        Mobilenet();
        ~Mobilenet();
        float *getInputBuffer();
        float predict();

};
#endif