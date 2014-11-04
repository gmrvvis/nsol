# generated by Buildyard, do not edit.

include(System)
list(APPEND FIND_PACKAGES_DEFINES ${SYSTEM})
find_package(PkgConfig)

# set(ENV{PKG_CONFIG_PATH} "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
# if(PKG_CONFIG_EXECUTABLE)
#   find_package(libzmq 4)
#   if((NOT libzmq_FOUND) AND (NOT LIBZMQ_FOUND))
#     pkg_check_modules(libzmq libzmq>=4)
#   endif()
#   if((NOT libzmq_FOUND) AND (NOT LIBZMQ_FOUND))
#     message(FATAL_ERROR "Could not find libzmq")
#   endif()
# else()
#   find_package(libzmq 4  REQUIRED)
# endif()

# if(PKG_CONFIG_EXECUTABLE)
#   find_package(FlatBuffers )
#   if((NOT FlatBuffers_FOUND) AND (NOT FLATBUFFERS_FOUND))
#     pkg_check_modules(FlatBuffers FlatBuffers)
#   endif()
#   if((NOT FlatBuffers_FOUND) AND (NOT FLATBUFFERS_FOUND))
#     message(FATAL_ERROR "Could not find FlatBuffers")
#   endif()
# else()
#   find_package(FlatBuffers   REQUIRED)
# endif()

# if(PKG_CONFIG_EXECUTABLE)
#   find_package(Boost 1.41.0 COMPONENTS unit_test_framework)
#   if((NOT Boost_FOUND) AND (NOT BOOST_FOUND))
#     pkg_check_modules(Boost Boost>=1.41.0)
#   endif()
#   if((NOT Boost_FOUND) AND (NOT BOOST_FOUND))
#     message(FATAL_ERROR "Could not find Boost COMPONENTS unit_test_framework")
#   endif()
# else()
#   find_package(Boost 1.41.0  REQUIRED unit_test_framework)
# endif()

# if(PKG_CONFIG_EXECUTABLE)
#   find_package(Lunchbox 1.10)
#   if((NOT Lunchbox_FOUND) AND (NOT LUNCHBOX_FOUND))
#     pkg_check_modules(Lunchbox Lunchbox>=1.10)
#   endif()
#   if((NOT Lunchbox_FOUND) AND (NOT LUNCHBOX_FOUND))
#     message(FATAL_ERROR "Could not find Lunchbox")
#   endif()
# else()
#   find_package(Lunchbox 1.10  REQUIRED)
# endif()


# if(EXISTS ${PROJECT_SOURCE_DIR}/CMake/FindPackagesPost.cmake)
#   include(${PROJECT_SOURCE_DIR}/CMake/FindPackagesPost.cmake)
# endif()

# if(LIBZMQ_FOUND)
#   set(libzmq_name LIBZMQ)
#   set(libzmq_FOUND TRUE)
# elseif(libzmq_FOUND)
#   set(libzmq_name libzmq)
#   set(LIBZMQ_FOUND TRUE)
# endif()
# if(libzmq_name)
#   list(APPEND FIND_PACKAGES_DEFINES ZEQ_USE_LIBZMQ)
#   set(FIND_PACKAGES_FOUND "${FIND_PACKAGES_FOUND} libzmq")
#   link_directories(${${libzmq_name}_LIBRARY_DIRS})
#   if(NOT "${${libzmq_name}_INCLUDE_DIRS}" MATCHES "-NOTFOUND")
#     include_directories(${${libzmq_name}_INCLUDE_DIRS})
#   endif()
# endif()



# Find package vmmlib which is required
find_package(vmmlib REQUIRED)
include_directories(${VMMLIB_INCLUDE_DIRS})
if(VMMLIB_FOUND)
  set(vmmlib_name LIBVMMLIB)
  set(vmmlib_FOUND TRUE)
elseif(vmmlib_FOUND)
  set(vmmlib_name libzmq)
  set(vmmlib_FOUND TRUE)
endif()
if(vmmlib_name)
  list(APPEND FIND_PACKAGES_DEFINES NSOL_WITH_VMMLIB)
  set(FIND_PACKAGES_FOUND "${FIND_PACKAGES_FOUND} vmmlib")
#  link_directories(${${vmmlib_name}_LIBRARY_DIRS})
  if(NOT "${${libvmmlib_name}_INCLUDE_DIRS}" MATCHES "-NOTFOUND")
    include_directories(${${libvmmlib_name}_INCLUDE_DIRS})
  endif()
endif()

# Find package BBPSDK which is optional
find_package(BBPSDK)

if(BBPSDK_FOUND)
  set(bbpsdk_name LIBBBPSDK)
  set(bbpsdk_FOUND TRUE)
elseif(bbpsdk_FOUND)
  set(bbpsdk_name libzmq)
  set(bbpsdk_FOUND TRUE)
endif()
if(bbpsdk_name)
  find_package(Boost 1.45.0 COMPONENTS system REQUIRED)
  list(APPEND FIND_PACKAGES_DEFINES NSOL_WITH_BBPSDK)
  set(FIND_PACKAGES_FOUND "${FIND_PACKAGES_FOUND} bbpsdk")
#  link_directories(${${bbpsdk_name}_LIBRARY_DIRS})
  if(NOT "${${libbbpsdk_name}_INCLUDE_DIRS}" MATCHES "-NOTFOUND")
    include_directories(${${libbbpsdk_name}_INCLUDE_DIRS})
  endif()
  list(APPEND NSOL_LIBRARIES ${BBPSDK_LIBRARIES})
endif()

# if (BBPSDK_FOUND)
#   include_directories(${BBPSDK_INCLUDE_DIRS})
#   add_definitions(-DWITH_BBPSDK)
# endif()


# Option of shared pointers
if (WITH_SHARED_PTR)
#  set(WITH_SHARED_PTR 1)
  list(APPEND FIND_PACKAGES_DEFINES NSOL_WITH_SHARED_PTR) 
endif()


# if(FLATBUFFERS_FOUND)
#   set(FlatBuffers_name FLATBUFFERS)
#   set(FlatBuffers_FOUND TRUE)
# elseif(FlatBuffers_FOUND)
#   set(FlatBuffers_name FlatBuffers)
#   set(FLATBUFFERS_FOUND TRUE)
# endif()
# if(FlatBuffers_name)
#   list(APPEND FIND_PACKAGES_DEFINES ZEQ_USE_FLATBUFFERS)
#   set(FIND_PACKAGES_FOUND "${FIND_PACKAGES_FOUND} FlatBuffers")
#   link_directories(${${FlatBuffers_name}_LIBRARY_DIRS})
#   if(NOT "${${FlatBuffers_name}_INCLUDE_DIRS}" MATCHES "-NOTFOUND")
#     include_directories(${${FlatBuffers_name}_INCLUDE_DIRS})
#   endif()
# endif()

# if(BOOST_FOUND)
#   set(Boost_name BOOST)
#   set(Boost_FOUND TRUE)
# elseif(Boost_FOUND)
#   set(Boost_name Boost)
#   set(BOOST_FOUND TRUE)
# endif()
# if(Boost_name)
#   list(APPEND FIND_PACKAGES_DEFINES ZEQ_USE_BOOST)
#   set(FIND_PACKAGES_FOUND "${FIND_PACKAGES_FOUND} Boost")
#   link_directories(${${Boost_name}_LIBRARY_DIRS})
#   if(NOT "${${Boost_name}_INCLUDE_DIRS}" MATCHES "-NOTFOUND")
#     include_directories(SYSTEM ${${Boost_name}_INCLUDE_DIRS})
#   endif()
# endif()

# if(LUNCHBOX_FOUND)
#   set(Lunchbox_name LUNCHBOX)
#   set(Lunchbox_FOUND TRUE)
# elseif(Lunchbox_FOUND)
#   set(Lunchbox_name Lunchbox)
#   set(LUNCHBOX_FOUND TRUE)
# endif()
# if(Lunchbox_name)
#   list(APPEND FIND_PACKAGES_DEFINES ZEQ_USE_LUNCHBOX)
#   set(FIND_PACKAGES_FOUND "${FIND_PACKAGES_FOUND} Lunchbox")
#   link_directories(${${Lunchbox_name}_LIBRARY_DIRS})
#   if(NOT "${${Lunchbox_name}_INCLUDE_DIRS}" MATCHES "-NOTFOUND")
#     include_directories(${${Lunchbox_name}_INCLUDE_DIRS})
#   endif()
# endif()

# set(ZEQ_BUILD_DEBS autoconf;automake;avahi-daemon;cmake;doxygen;git;git-review;libavahi-client-dev;libboost-filesystem-dev;libboost-regex-dev;libboost-serialization-dev;libboost-system-dev;libboost-test-dev;libboost-thread-dev;libhwloc-dev;libjpeg-turbo8-dev;libleveldb-dev;libopenmpi-dev;libturbojpeg;libzmq3-dev;openmpi-bin;pkg-config;subversion)

# set(ZEQ_DEPENDS libzmq;FlatBuffers;Boost;Lunchbox)

# Write defines.h and options.cmake
if(NOT PROJECT_INCLUDE_NAME)
  message(WARNING "PROJECT_INCLUDE_NAME not set, old or missing Common.cmake?")
  set(PROJECT_INCLUDE_NAME ${PROJECT_NAME})
endif()
if(NOT OPTIONS_CMAKE)
  set(OPTIONS_CMAKE ${CMAKE_CURRENT_BINARY_DIR}/options.cmake)
endif()
set(DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_INCLUDE_NAME}/defines${SYSTEM}.h")
list(APPEND COMMON_INCLUDES ${DEFINES_FILE})
set(DEFINES_FILE_IN ${DEFINES_FILE}.in)
file(WRITE ${DEFINES_FILE_IN}
  "// generated by CMake/FindPackages.cmake, do not edit.\n\n"
  "#ifndef ${PROJECT_NAME}_DEFINES_${SYSTEM}_H\n"
  "#define ${PROJECT_NAME}_DEFINES_${SYSTEM}_H\n\n")
file(WRITE ${OPTIONS_CMAKE} "# Optional modules enabled during build\n")
foreach(DEF ${FIND_PACKAGES_DEFINES})
  add_definitions(-D${DEF}=1)
  file(APPEND ${DEFINES_FILE_IN}
  "#ifndef ${DEF}\n"
  "#  define ${DEF} 1\n"
  "#endif\n")
if(NOT DEF STREQUAL SYSTEM)
  file(APPEND ${OPTIONS_CMAKE} "set(${DEF} ON)\n")
endif()
endforeach()
if(CMAKE_MODULE_INSTALL_PATH)
  install(FILES ${OPTIONS_CMAKE} DESTINATION ${CMAKE_MODULE_INSTALL_PATH}
    COMPONENT dev)
else()
  message(WARNING "CMAKE_MODULE_INSTALL_PATH not set, old or missing Common.cmake?")
endif()
file(APPEND ${DEFINES_FILE_IN}
  "\n#endif\n")

include(UpdateFile)
configure_file(${DEFINES_FILE_IN} ${DEFINES_FILE} COPYONLY)

# if(Boost_FOUND) # another WAR for broken boost stuff...
#   set(Boost_VERSION ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION})
# endif()
# if(CUDA_FOUND)
#   string(REPLACE "-std=c++11" "" CUDA_HOST_FLAGS "${CUDA_HOST_FLAGS}")
#   string(REPLACE "-std=c++0x" "" CUDA_HOST_FLAGS "${CUDA_HOST_FLAGS}")
# endif()
# if(OPENMP_FOUND)
#   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
# endif()
# if(QT4_FOUND)
#   if(WIN32)
#     set(QT_USE_QTMAIN TRUE)
#   endif()
#   # Configure a copy of the 'UseQt4.cmake' system file.
#   if(NOT EXISTS ${QT_USE_FILE})
#     message(WARNING "Can't find QT_USE_FILE!")
#   else()
#     set(_customUseQt4File "${CMAKE_CURRENT_BINARY_DIR}/UseQt4.cmake")
#     file(READ ${QT_USE_FILE} content)
#     # Change all include_directories() to use the SYSTEM option
#     string(REPLACE "include_directories(" "include_directories(SYSTEM " content ${content})
#     string(REPLACE "INCLUDE_DIRECTORIES(" "INCLUDE_DIRECTORIES(SYSTEM " content ${content})
#     file(WRITE ${_customUseQt4File} ${content})
#     set(QT_USE_FILE ${_customUseQt4File})
#     include(${QT_USE_FILE})
#   endif()
# endif()
if(FIND_PACKAGES_FOUND)
  if(MSVC)
    message(STATUS "Configured ${PROJECT_NAME} with ${FIND_PACKAGES_FOUND}")
  else()
    message(STATUS "Configured ${PROJECT_NAME} with ${CMAKE_BUILD_TYPE}${FIND_PACKAGES_FOUND}")
  endif()
endif()
