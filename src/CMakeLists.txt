
add_executable(audio_main "")

target_sources(audio_main 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/read_wav.cpp
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/read_wav.h
)

target_include_directories(audio_main
    PUBLIC 
        ${PROJECT_INCLUDE_DIR}
)
