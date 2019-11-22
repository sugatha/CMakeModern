cmake_minimum_required(VERSION 3.6.2)
project(moderncmakedemo)

include(SetUpConfigurations.cmake)
include(dependency-graph.cmake)

set( CMAKE_POSITION_INDEPENDENT_CODE ON )

# setting the output location
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../bin")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../bin")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../Test")

# This will help in making use of the ccache to speeden-up the compilation.
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

# adding the subdirectories in this project - the sequence of including is important
#add_subdirectory(mylib_1)
#add_subdirectory(mylib_2)
#add_subdirectory(theapp)

########################################################
# building exe - theapp


add_executable(theapp ${CMAKE_SOURCE_DIR}/theapp/main.cpp)



#message(STATUS "INSIDE theapp")
set(BUILD_FLAGS "/DMYTEST")
#message(STATUS "Before - ${COMPILE_FLAGS}")
#set_target_properties(theapp APPEND PROPERTIES COMPILE_FLAGS ${BUILD_FLAGS})
#target_compile_options(theapp PRIVATE <${CMAKE_C_FLAGS_TEST}:${BUILD_FLAGS}>)
#target_compile_options(theapp PRIVATE <${CMAKE_CXX_FLAGS_TEST}:${BUILD_FLAGS}>)
#[[
target_compile_options(${TARGET} PRIVATE
          $<$<COMPILE_LANGUAGE:CXX>:${BUILD_FLAGS}>
          $<$<COMPILE_LANGUAGE:C>:${BUILD_FLAGS}>)
		  ]]

#message(STATUS "After - ${COMPILE_FLAGS}")
set_source_files_properties(${CMAKE_SOURCE_DIR}/theapp/main.cpp PROPERTIES COMPILE_FLAGS ${BUILD_FLAGS})


target_include_directories(theapp PUBLIC ${CMAKE_SOURCE_DIR}/mylib_1)
target_link_libraries(theapp PUBLIC mylib_1)
#[[target_link_libraries(theapp debug mylib_1)
target_link_libraries(theapp optimized mylib_1)
]]

#-resetting 
#string(REPLACE "/DMYTEST" "" CMAKE_C_FLAGS_TEST "${CMAKE_C_FLAGS_TEST}")
#string(REPLACE "/DMYTEST" "" CMAKE_CXX_FLAGS_TEST "${CMAKE_CXX_FLAGS_TEST}")


####################################################



#####################################
# building library - mylib_1
#link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(resources ${CMAKE_SOURCE_DIR}/mylib_1/mylib_1.cpp ${CMAKE_SOURCE_DIR}/mylib_1/mylib_1.h)
add_library(mylib_1 STATIC ${resources})
target_include_directories(mylib_1 PUBLIC ${CMAKE_SOURCE_DIR}/mylib_2 ${CMAKE_SOURCE_DIR}/mylib_1)
target_link_libraries(mylib_1 PUBLIC mylib_2)

###########################################
# building library - mylib_2
#[[set(source ${CMAKE_SOURCE_DIR}/mylib_2/mylib_2.cpp)
set(header ${CMAKE_SOURCE_DIR}/mylib_2/mylib_2.h)
add_library("mylib_2" STATIC ${source} ${header})
#]]
#######################################################


## add sources later to the library
file(GLOB myheader *.h)
file(GLOB sources *.cpp)
add_library(mylib_2 STATIC)
target_sources(mylib_2 PUBLIC ${CMAKE_SOURCE_DIR}/mylib_2/mylib_2.cpp ${myheader})

#[[
target_compile_options(mylib_2 PUBLIC
          $<$<COMPILE_LANGUAGE:CXX>:${BUILD_FLAGS}>
          $<$<COMPILE_LANGUAGE:C>:${BUILD_FLAGS}>)
		  ]]
#set_property(TARGET mylib_2 PROPERTIES COMPILE_FLAGS "")
########################################################
# building exe - theapp
#[[
add_executable(theapp ${CMAKE_SOURCE_DIR}/theapp/main.cpp)

set(CMAKE_C_FLAGS_TEST "${CMAKE_C_FLAGS_TEST} /DMYTEST")
set(CMAKE_CXX_FLAGS_TEST "${CMAKE_C_FLAGS_TEST} /DMYTEST")

target_include_directories(theapp PUBLIC ${CMAKE_SOURCE_DIR}/mylib_1)
target_link_libraries(theapp debug mylib_1)
target_link_libraries(theapp optimized mylib_1)
#]]
####################################################

message (STATUS "calling add_custom_target")

message(STATUS "{CMAKE_SOURCE_DIR} - ${CMAKE_SOURCE_DIR}" )

generate_graph(png)

add_dependencies(mylib_1 mylib_2)
add_dependencies(theapp mylib_1)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT theapp)