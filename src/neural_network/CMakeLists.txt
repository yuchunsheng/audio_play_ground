
add_library(neural_network "")

target_sources(neural_network
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/hello_world_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/model.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/model.h
          
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/hello_world_test.h

)
target_link_libraries(neural_network "generic-tflmicro")
# target_link_libraries(neural_network ${PROJECT_LIB_DIR}/libtensorflow-microlite.a)

# target_include_directories(neural_network
#     PUBLIC 
#         ${PROJECT_INCLUDE_DIR}
#         ${PROJECT_INCLUDE_DIR}/third_party/flatbuffers/include
# )
