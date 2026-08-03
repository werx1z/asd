cmake_minimum_required(VERSION 3.15)
project(Standoff2ESP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fobjc-arc -std=c++17 -O2")

set(SOURCES
    main.mm
    Core/Memory.cpp
    Core/ESP.cpp
    Core/SilentAim.cpp
    Core/AntiCheat.cpp
    UI/Config.cpp
)

add_library(Standoff2ESP SHARED ${SOURCES})

target_include_directories(Standoff2ESP PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/UI
)

target_link_libraries(Standoff2ESP
    "-framework Foundation"
    "-framework UIKit"
    "-framework CoreGraphics"
    "-lc++"
)

set_target_properties(Standoff2ESP PROPERTIES
    SUFFIX ".dylib"
    PREFIX ""
    LINK_FLAGS "-dynamiclib -undefined dynamic_lookup"
)
