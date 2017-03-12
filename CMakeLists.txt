cmake_minimum_required(VERSION 3.3.0)

project(TMX++ CXX)

add_library(tmxpp
    src/exceptions.cpp
    src/read.cpp
    src/write.cpp
    src/impl/exceptions.cpp
    src/impl/Xml.cpp)
target_include_directories(tmxpp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

find_package(Boost.Hana QUIET)
if (Boost.Hana_FOUND)
    target_link_libraries(tmxpp PUBLIC hana)
else()
    find_package(Boost 1.61.0 REQUIRED)
    target_link_libraries(tmxpp PUBLIC Boost::boost)
endif()

find_package(jegp 3.0.0 REQUIRED)
find_package(RapidXml 5.0.0 REQUIRED)
target_link_libraries(tmxpp
    PUBLIC jegp
    PRIVATE RapidXml)

if (NOT 3.8.0 VERSION_GREATER CMAKE_VERSION)
    target_compile_features(tmxpp PUBLIC cxx_std_17)
else()
    target_compile_options(tmxpp PUBLIC -std=c++1z)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
    target_link_libraries(tmxpp INTERFACE stdc++fs)
endif()

install(TARGETS tmxpp EXPORT tmxppTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

export(EXPORT tmxppTargets FILE tmxppTargets.cmake)
configure_file(tmxppConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/tmxppConfig.cmake
    COPYONLY)

install(EXPORT tmxppTargets DESTINATION cmake)
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/tmxppConfig.cmake
    DESTINATION cmake)
