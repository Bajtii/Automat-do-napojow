# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Automat-do-napojow_autogen"
  "CMakeFiles\\Automat-do-napojow_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Automat-do-napojow_autogen.dir\\ParseCache.txt"
  )
endif()
