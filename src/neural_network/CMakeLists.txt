
add_library(neural_network "")

target_sources(neural_network
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/hello_world_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/model.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/model.h
          
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/hello_world_test.h

)

target_include_directories(neural_network
    PUBLIC 
        ${PROJECT_INCLUDE_DIR}
)