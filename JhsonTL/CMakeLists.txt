cmake_minimum_required(VERSION 3.11)

project(
  JhsonTL
  VERSION 0.2
  DESCRIPTION "Custom template libraries by Janghyun Son"
  LANGUAGES CXX)


add_executable (app.out main.cpp)

target_include_directories (app.out PUBLIC ${CMAKE_SOURCE_DIR}/includes ${CMAKE_SOURCE_DIR}/test)    
add_subdirectory(test)
target_link_libraries(app.out PUBLIC tests)
