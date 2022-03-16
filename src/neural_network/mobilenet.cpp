
#include <iostream>

#include "mobilenet.h"
#include "mobilenetv1.h"

// approximate working size of our model
const int kArenaSize = 5*1024*1024;  //5M bytes required

Mobilenet::Mobilenet()
{
    static tflite::MicroErrorReporter micro_error_reporter;
    m_error_reporter = &micro_error_reporter;

    m_tensor_arena = (uint8_t *)malloc(kArenaSize);
    if (!m_tensor_arena)
    {
        TF_LITE_REPORT_ERROR(m_error_reporter, "Could not allocate arena");
        return;
    }
    TF_LITE_REPORT_ERROR(m_error_reporter, "Loading model");

    m_model = tflite::GetModel(mobilenetv1_no_quant_tflite);
    if (m_model->version() != TFLITE_SCHEMA_VERSION)
    {
        TF_LITE_REPORT_ERROR(m_error_reporter, "Model provided is schema version %d not equal to supported version %d.",
                             m_model->version(), TFLITE_SCHEMA_VERSION);
        return;
    }
    // This pulls in the operators implementations we need
    tflite::AllOpsResolver m_resolver;

    // m_resolver = new tflite::MicroMutableOpResolver<10>();
    // m_resolver->AddConv2D();
    // m_resolver->AddMaxPool2D();
    // m_resolver->AddFullyConnected();
    // m_resolver->AddMul();
    // m_resolver->AddAdd();
    // m_resolver->AddLogistic();
    // m_resolver->AddReshape();
    // m_resolver->AddQuantize();
    // m_resolver->AddDequantize();

    // Build an interpreter to run the model with.
    // m_interpreter = new tflite::MicroInterpreter(
    //     m_model, *m_resolver, m_tensor_arena, kArenaSize, m_error_reporter);

    m_interpreter = new tflite::MicroInterpreter(
        m_model, m_resolver, m_tensor_arena, kArenaSize, m_error_reporter);

    // Allocate memory from the tensor_arena for the model's tensors.
    TfLiteStatus allocate_status = m_interpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk)
    {
        TF_LITE_REPORT_ERROR(m_error_reporter, "AllocateTensors() failed");
        return;
    }

    size_t used_bytes = m_interpreter->arena_used_bytes();
    TF_LITE_REPORT_ERROR(m_error_reporter, "Used bytes %d\n", used_bytes);

    // Obtain pointers to the model's input and output tensors.
    input = m_interpreter->input(0);
    output = m_interpreter->output(0);
}

Mobilenet::~Mobilenet()
{
    delete m_interpreter;
    delete m_resolver;
    free(m_tensor_arena);
    delete m_error_reporter;
}

float *Mobilenet::getInputBuffer()
{
    return input->data.f;
}

float Mobilenet::predict()
{
    m_interpreter->Invoke();
    return output->data.f[0];
}