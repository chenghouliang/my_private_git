# Copyright (C) 2015 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 2.8)

set(PRJ_NAME ModuleXXX)

set(CMAKE_VERBOSE_MAKEFILE on)

OPTION(USE_FILE "Set to OFF to disable file logging" OFF )
message(STATUS "USE_FILE is set to value: ${USE_FILE}")

OPTION(USE_CONSOLE "Set to OFF to disable console logging" OFF )
message(STATUS "USE_CONSOLE is set to value: ${USE_CONSOLE}")
# set(CommonAPI_DIR "/home/chenghl/CommonAPI/capicxx-core-runtime/build")
# set(COMMONAPI_INCLUDE_DIRS "/home/chenghl/CommonAPI/capicxx-core-runtime/include")
# set(COMMONAPI_SOMEIP_INCLUDE_DIRS "/home/chenghl/CommonAPI/capicxx-someip-runtime/include")
# set(VSOMEIP_INCLUDE_DIRS "/home/chenghl/CommonAPI/vsomeip/interface")
#set(CMAKE_C_COMPILER "/opt/AG55X/ql-ag550qcn-le20-gcc820-v1-toolchain/gcc/usr/bin/arm-oe-linux/arm-oe-linux-gcc")
#set(CMAKE_CXX_COMPILER "/opt/AG55X/ql-ag550qcn-le20-gcc820-v1-toolchain/gcc/usr/bin/arm-oe-linux/arm-oe-linux-g++")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${LIBHEBI_CROSS_GCC_TOOLCHAIN_ARG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LIBHEBI_CROSS_GCC_TOOLCHAIN_ARG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -O0 -std=c++11 -D_GLIBCXX_USE_NANOSLEEP -DLINUX")

IF(USE_FILE)
  add_definitions(-DUSE_FILE)
ENDIF(USE_FILE)
IF(USE_CONSOLE)
  add_definitions(-DUSE_CONSOLE)
ENDIF(USE_CONSOLE)

SET(MAX_LOG_LEVEL "DEBUG" CACHE STRING "maximum log level")
message(STATUS "MAX_LOG_LEVEL is set to value: ${MAX_LOG_LEVEL}")
add_definitions(-DCOMMONAPI_LOGLEVEL=COMMONAPI_LOGLEVEL_${MAX_LOG_LEVEL})

message(STATUS "Compiler options: ${CMAKE_CXX_FLAGS}") 

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
       "Choose the type of build, options are: Debug Release." FORCE)
endif(NOT CMAKE_BUILD_TYPE)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

OPTION(USE_INSTALLED_COMMONAPI "Set to OFF to use the local (build tree) version of CommonAPI" ON)
message(STATUS "USE_INSTALLED_COMMONAPI is set to value: ${USE_INSTALLED_COMMONAPI}")

# if ("${USE_INSTALLED_COMMONAPI}" STREQUAL "ON")
#     FIND_PACKAGE(CommonAPI 3.2.0 REQUIRED CONFIG NO_CMAKE_PACKAGE_REGISTRY)
# else()
    FIND_PACKAGE(CommonAPI 3.2.0 REQUIRED CONFIG NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH)
# endif()



# CommonAPI
include(FindPkgConfig)
###############################################################################
# SOME/IP
find_package (CommonAPI-SomeIP 3.2.0 REQUIRED)
find_package (vsomeip3 3.1.20 REQUIRED)
# Boost
find_package( Boost 1.54 COMPONENTS system thread log REQUIRED )
message(STATUS "CommonAPI_CONSIDERED_CONFIGS: ${CommonAPI_CONSIDERED_CONFIGS}")
message(STATUS "COMMONAPI_INCLUDE_DIRS: ${COMMONAPI_INCLUDE_DIRS}")
message(STATUS "COMMONAPI_SOMEIP_INCLUDE_DIRS: ${COMMONAPI_SOMEIP_INCLUDE_DIRS}")
message(STATUS "VSOMEIP_INCLUDE_DIRS: ${VSOMEIP_INCLUDE_DIRS}")
message(STATUS "Boost_INCLUDE_DIR: ${Boost_INCLUDE_DIR}")
include_directories(
    src
    src-gen
    ${COMMONAPI_INCLUDE_DIRS}
    ${COMMONAPI_SOMEIP_INCLUDE_DIRS}
    ${VSOMEIP_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIR}
)

# /home/chenghl/CommonAPI/capicxx-core-runtime/build
# /home/chenghl/CommonAPI/capicxx-someip-runtime/build
# /home/chenghl/CommonAPI/vsomeip/build
message(STATUS "COMMONAPI_LIBDIR: ${COMMONAPI_LIBDIR}")
message(STATUS "COMMONAPI_SOMEIP_CMAKE_DIR: ${COMMONAPI_SOMEIP_CMAKE_DIR}")
message(STATUS "Boost_LIBRARY_DIR: ${Boost_LIBRARY_DIR}")
link_directories(
    ${COMMONAPI_LIBDIR}
    ${COMMONAPI_SOMEIP_CMAKE_DIR}/build
    ${Boost_LIBRARY_DIR}
)

# Source Files
set(PRJ_SRC_PATH src)
set(PRJ_NAME_CLIENT ${PRJ_NAME}Client)
set(PRJ_NAME_SERVICE ${PRJ_NAME}Service)
# Application
FILE(GLOB PRJ_PROXY_GEN_SRCS src-gen/v0/commonapi/examples/*.cpp)

set(LINK_LIBRARIES -Wl,--as-needed CommonAPI)

add_library (${PRJ_NAME_CLIENT}If SHARED  ${PRJ_SRC_PATH}/${PRJ_NAME_CLIENT}Impl.cpp ${PRJ_PROXY_GEN_SRCS})
target_link_libraries(${PRJ_NAME_CLIENT}If CommonAPI-SomeIP)

add_library (${PRJ_NAME_SERVICE}If SHARED ${PRJ_SRC_PATH}/${PRJ_NAME_SERVICE}Impl.cpp ${PRJ_PROXY_GEN_SRCS})
target_link_libraries(${PRJ_NAME_SERVICE}If CommonAPI-SomeIP)