cmake_minimum_required(VERSION 3.11)

project(
  JhsonTL
  VERSION 0.1
  DESCRIPTION "Custom template libraries by Janghyun Son"
  LANGUAGES CXX)


add_executable (app.out main.cpp)

target_include_directories (app.out PUBLIC ${CMAKE_SOURCE_DIR}/Vector)    

