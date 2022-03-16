
add_library(image_processing "")

target_sources(image_processing
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/image_provider.h
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/image_provider.cpp
)

# target_link_libraries(image_processing
#     PUBLIC tjpg_decoder
# )