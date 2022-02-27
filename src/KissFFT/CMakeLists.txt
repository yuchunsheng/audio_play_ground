add_library(kissfft STATIC "")

target_sources(kissfft 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/kiss_fft.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/kiss_fftr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/_kiss_fft_guts.h
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/kiss_fft.h
        ${CMAKE_CURRENT_SOURCE_DIR}/kiss_fftr.h
        ${CMAKE_CURRENT_SOURCE_DIR}/kiss_fft_log.h

    
)
