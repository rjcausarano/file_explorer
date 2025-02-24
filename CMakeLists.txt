cmake_minimum_required(VERSION 3.30)
project(file_explorer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(sockets)

# Find wx-config
find_program(WX_CONFIG_EXECUTABLE ../wxWidgets-3.2.6/build-cocoa-debug/wx-config)

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

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/sockets/include
)

set(SOURCES
  src/file.cc
  src/main_frame.cc
  src/entity_processor.cc
)

set(TEST_FILES
  test/command_processor.cc
  src/entity_processor.cc
)

add_executable(${PROJECT_NAME} src/main.cc ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${WX_LINKER_FLAGS} comms)

add_executable(test test/test.cc ${TEST_FILES} ${SOURCES})
target_link_libraries(test comms)

add_executable(server test/server_main.cc ${TEST_FILES} ${SOURCES})
target_link_libraries(server comms)

add_executable(client test/client_main.cc ${TEST_FILES} ${SOURCES})
target_link_libraries(client comms)
