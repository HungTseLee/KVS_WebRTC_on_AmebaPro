/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_OBJECT_DETECTION_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_OBJECT_DETECTION_H_

// Expose a C friendly interface for main functions.
#ifdef __cplusplus
extern "C" {
#endif
    enum tflm_model_select {
	human_300_025_int8_post,
	human_224_025_int8_post,
	face_224_025_int8_post
    };
    
    void object_detection_setup(int selected_model);
    void object_detection(unsigned char* input_buffer, 
                            int input_width,
                            int input_height,
                            int input_format,
                            float* output_boxes,
                            float* output_classes,
                            float* output_scores,
                            int* output_num_detections,
                            int padding_zero);

#ifdef __cplusplus
}
#endif

#endif  // TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_MAIN_FUNCTIONS_H_
