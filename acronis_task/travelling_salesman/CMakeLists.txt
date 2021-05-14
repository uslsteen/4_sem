cmake_minimum_required(VERSION 3.13.4)
project(Traveller)

find_package(BISON 3.7 REQUIRED)
find_package(FLEX REQUIRED)


set(TRAVELLER  "${PROJECT_NAME}i")

message(STATUS "Traveller: ${TR_NAME}")

# option for debug (debug info)
set(PR_DEBUG_OPTIONS -g)

# option for release (optimization)
set(PR_RELEASE_OPTIONS -O2)

# some useful warnings
set(WARN_OPTIONS
  -Wall 
   #-Wextra commented because it causes warnings at llvm library code
  -Wunused -Wpedantic # classic
  -Wno-old-style-cast #-Waggressive-loop-optimizations
  -Wunreachable-code)

flex_target(
  flex_o
  grammar/lexer.l
  ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cc
)

bison_target(
  bison_o
  grammar/compiler.y
  ${CMAKE_CURRENT_BINARY_DIR}/compiler.tab.cc
  COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/compiler.tab.hh")

add_flex_bison_dependency(flex_o bison_o)

add_executable(${TRAVELLER} 
  main.cc
  ${BISON_bison_o_OUTPUTS}
  ${FLEX_flex_o_OUTPUTS}
  driver/driver.cc
  parser/parser.cc
  graph/graph.cc
  algo/algorithm.cc
)

set(TARGETS ${TRAVELLER})

# use llvm-config --components and some guessing to determine components

foreach(TARGET ${TARGETS})
  target_compile_features(${TARGET} PRIVATE cxx_std_17)
  target_compile_options(${TARGET} PRIVATE ${WARN_OPTIONS})
  
  target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
  target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_include_directories(${TARGET} PRIVATE driver) 
  target_include_directories(${TARGET} PRIVATE parser)
  target_include_directories(${TARGET} PRIVATE matrix)
  target_include_directories(${TARGET} PRIVATE graph)
  target_include_directories(${TARGET} PRIVATE algo)

  # Specify compiler options for debug and release
  target_compile_options(${TARGET} PRIVATE "$<$<CONFIG:DEBUG>:${PR_DEBUG_OPTIONS}>")
  target_compile_options(${TARGET} PRIVATE "$<$<CONFIG:RELEASE>:${PR_RELEASE_OPTIONS}>")

endforeach()

