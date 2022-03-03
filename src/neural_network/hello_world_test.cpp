
#include <iostream>

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"

#include "model.h"
#include "hello_world_test.h"

// Globals, used for compatibility with Arduino-style sketches.
namespace {
    tflite::ErrorReporter* error_reporter = nullptr;
    const tflite::Model* model = nullptr;
    tflite::MicroInterpreter* interpreter = nullptr;
    TfLiteTensor* input = nullptr;
    TfLiteTensor* output = nullptr;
    int inference_count = 0;

    constexpr int kTensorArenaSize = 2*1024;
    uint8_t tensor_arena[kTensorArenaSize];
}  // namespace


// The name of this function is important for Arduino compatibility.
void setup() {
  tflite::InitializeTarget();

  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(g_hello_world_model_data);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  // This pulls in all the operation implementations we need.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::AllOpsResolver resolver;

  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }

  // Obtain pointers to the model's input and output tensors.
  input = interpreter->input(0);
  output = interpreter->output(0);

  // Keep track of how many inferences we have performed.
  inference_count = 10;
}

void run_hello_world_test(){
    std::cout << "tflite micro input!\n";

    setup();
    const float kXrange = 2.f * 3.14159265359f;
    const int kInferencesPerCycle = 20;

    float position = static_cast<float>(inference_count) /static_cast<float>(kInferencesPerCycle);
    // float x = position * kXrange;
    float x = 3.14;
    std::cout<<x<<std::endl;

    // Quantize the input from floating-point to integer
    int8_t x_quantized = x / input->params.scale + input->params.zero_point;
    std::cout<<input->params.scale << "  " << input->params.zero_point << std::endl;

    std::cout<<int(x_quantized)<<std::endl;

    // Place the quantized input in the model's input tensor
    input->data.int8[0] = x_quantized;
    //input->data.f[0]=x;
    // Run inference, and report any error
    TfLiteStatus invoke_status = interpreter->Invoke();
    if (invoke_status != kTfLiteOk) {
      TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed on x: %f\n",
                            static_cast<double>(x));
      }else {
            // Obtain the quantized output from model's output tensor
      int8_t y_quantized = output->data.int8[0];

      std::cout<<int(y_quantized)<<std::endl;
      // Dequantize the output from integer to floating-point
      float y = (y_quantized - output->params.zero_point) * output->params.scale;
      //float y = output->data.f[0];

      TF_LITE_REPORT_ERROR(error_reporter, "x_value: %f, y_value: %f\n",
                        static_cast<double>(x),
                        static_cast<double>(y));

    }
    
}

    
