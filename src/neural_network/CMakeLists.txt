
add_library(neural_network "")

target_sources(neural_network
    PRIVATE
        # ${CMAKE_CURRENT_SOURCE_DIR}/hello_world_test.cpp
        # ${CMAKE_CURRENT_SOURCE_DIR}/model.cpp
        # ${CMAKE_CURRENT_SOURCE_DIR}/model.h
        ${CMAKE_CURRENT_SOURCE_DIR}/command_model.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/speech_command.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/command_model.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mobilenet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mobilenetv1.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mobilenetv1.h
          
    PUBLIC
        # ${CMAKE_CURRENT_SOURCE_DIR}/hello_world_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/speech_command.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mobilenet.h

)
target_link_libraries(neural_network "generic-tflmicro")
# target_link_libraries(neural_network ${PROJECT_LIB_DIR}/libtensorflow-microlite.a)

# target_include_directories(neural_network
#     PUBLIC 
#         ${PROJECT_INCLUDE_DIR}
#         ${PROJECT_INCLUDE_DIR}/third_party/flatbuffers/include
# )
