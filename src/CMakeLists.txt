
set(kissfft_include ${CMAKE_CURRENT_SOURCE_DIR}/KissFFT)
set(utils_include ${CMAKE_CURRENT_SOURCE_DIR}/utils)

add_subdirectory(KissFFT)
add_subdirectory(audio_process)

add_executable(audio_main "")

target_sources(audio_main 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/audio_input/read_wav.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/audio_process/AudioProcessor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/audio_process/HammingWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/KissFFT/kiss_fft.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/KissFFT/kiss_fftr.cpp

    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/audio_input/read_wav.h
        ${CMAKE_CURRENT_SOURCE_DIR}/audio_process/AudioProcessor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/audio_process/HammingWindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/KissFFT/kiss_fft.h
        ${CMAKE_CURRENT_SOURCE_DIR}/KissFFT/kiss_fftr.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/RingBuffer.h

)

target_link_libraries(audio_main PUBLIC audio_processor)

target_include_directories(audio_main
    PUBLIC 
        ${PROJECT_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/audio_input 
        ${CMAKE_CURRENT_SOURCE_DIR}/audio_process 
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
)
