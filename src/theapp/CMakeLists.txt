#[[cmake_minimum_required(VERSION 3.6.2)
project(theapp)
message(STATUS "INSIDE theapp")
set(BUILD_FLAGS "/DMYTEST")
message(STATUS "Before - ${COMPILE_FLAGS}")
set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS ${BUILD_FLAGS})

#set(CMAKE_CXX_FLAGS_TEST "${CMAKE_C_FLAGS_TEST} /DMYTEST")
message(STATUS "After - ${COMPILE_FLAGS}")

add_executable(theapp ${CMAKE_SOURCE_DIR}/theapp/main.cpp)
target_include_directories(theapp PUBLIC ${CMAKE_SOURCE_DIR}/mylib_1)
target_link_libraries(theapp debug mylib_1)
target_link_libraries(theapp optimized mylib_1)

]]
set(BUILD_FLAGS "/DMYTEST")
target_compile_options(theapp PRIVATE
          $<$<COMPILE_LANGUAGE:CXX>:${BUILD_FLAGS}>
          $<$<COMPILE_LANGUAGE:C>:${BUILD_FLAGS}>)