cmake_minimum_required(VERSION 3.10)
project(file_explorer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find wx-config
find_program(WX_CONFIG_EXECUTABLE ../wxWidgets-3.2.6/build-cocoa-debug/wx-config)

find_package(Protobuf REQUIRED CONFIG)

if (NOT WX_CONFIG_EXECUTABLE)
  message(FATAL_ERROR "wx-config not found! Please ensure wxWidgets is installed.")
endif()

# Get compiler and linker flags from wx-config
execute_process(
  COMMAND ${WX_CONFIG_EXECUTABLE} --cxxflags
  OUTPUT_VARIABLE WX_CXX_FLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
  COMMAND ${WX_CONFIG_EXECUTABLE} --libs
  OUTPUT_VARIABLE WX_LINKER_FLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Add flags to your project
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WX_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${WX_LINKER_FLAGS}")

include_directories(${Protobuf_INCLUDE_DIRS})

set(SOURCES
  src/file.cc
  src/main_frame.cc
  src/file_serializer.cc
  proto/dir_descriptor.pb.cc
)

set(TEST_FILES
  test/test.cc
)

# Add your executable
add_executable(${PROJECT_NAME} src/main.cc ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} ${WX_LINKER_FLAGS} protobuf::libprotobuf)

add_executable(test ${TEST_FILES} ${SOURCES})
target_include_directories(test PRIVATE include)
target_link_libraries(test PRIVATE protobuf::libprotobuf)
