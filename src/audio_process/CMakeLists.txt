add_library(audio_processor STATIC "")

target_sources(audio_processor
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/AudioProcessor.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/HammingWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AudioDataProcessor.cpp

    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/AudioProcessor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/HammingWindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/AudioDataProcessor.h

)
message(STATUS "kissfft include dir: ${kissfft_include}")

target_include_directories(audio_processor
    PUBLIC 
        ${kissfft_include}
        ${utils_include}
)
target_link_libraries(
    audio_processor kissfft
)