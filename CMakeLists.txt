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
    $<INSTALL_INTERFACE:include>)

include(find_dependencies.cmake)
target_link_libraries(tmxpp
    PUBLIC
    #   GSL
        $<$<BOOL:${Boost.Hana_FOUND}>:hana>
        $<$<NOT:$<BOOL:${Boost.Hana_FOUND}>>:Boost::boost>
        jegp
    PRIVATE
    #   Range-v3
        RapidXml)

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

set(cmake_files tmxppConfig.cmake find_dependencies.cmake)

export(EXPORT tmxppTargets)
foreach(cfile IN LISTS cmake_files)
    configure_file(${cfile} ${cfile} COPYONLY)
endforeach()

install(EXPORT tmxppTargets  DESTINATION lib/cmake/tmxpp)
install(FILES ${cmake_files} DESTINATION lib/cmake/tmxpp)
