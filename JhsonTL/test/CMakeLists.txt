file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(tests  SHARED ${SRC_FILES})

target_include_directories (tests PUBLIC ${CMAKE_SOURCE_DIR}/includes)    

