cmake_minimum_required(VERSION 2.8)
######################################################################################################
set(TARGET "AG550")

if("${TARGET}" STREQUAL "AG550")
  set(TOOLCHAIN_DIR "/opt/AG55X/gcc-arm-8.2-2019.01-x86_64-arm-linux-gnueabi/bin")
  set(CMAKE_C_COMPILER "${TOOLCHAIN_DIR}/arm-linux-gnueabihf-gcc")
  set(CMAKE_CXX_COMPILER "${TOOLCHAIN_DIR}/arm-linux-gnueabihf-g++")
  set(MYSYSROOT "/opt/AG55X/gcc-arm-8.2-2019.01-x86_64-arm-linux-gnueabi/sysroot")

  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --sysroot=${MYSYSROOT}" CACHE INTERNAL "" FORCE)
  set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} --sysroot=${MYSYSROOT}" CACHE INTERNAL "" FORCE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --sysroot=${MYSYSROOT}" CACHE INTERNAL "" FORCE)
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} --sysroot=${MYSYSROOT}" CACHE INTERNAL "" FORCE)
  set(CMAKE_FIND_ROOT_PATH "${MYSYSROOT}")

  set(CORE_RUNTIME_INCLUDE_DIR "/home/chenghl/AG550/includeDirCommonAPI_AG550/capicxx-core-runtime")
  set(SOMEIP_RUNTIME_INCLUDE_DIR "/home/chenghl/AG550/includeDirCommonAPI_AG550/capicxx-someip-runtime")
  set(VSOMEIP_INCLUDE_DIR "/home/chenghl/AG550/includeDirCommonAPI_AG550/vsomeip")
  set(BOOST_INCLUDE_DIR "/home/chenghl/AG550/includeDirCommonAPI_AG550/boost_1_72")
  # set(COMMONAPI_LINK_DIR "/home/chenghl/AG550/libDirCommonAPI_AG550/commonapi")
  set(BOOST_LINK_DIR "/home/chenghl/AG550/libDirCommonAPI_AG550/boost_1_72")
elseif("${TARGET}" STREQUAL "AG215S")
  set(TOOLCHAIN_DIR "/opt/AG215X/toolchain/sysroots/x86_64-oesdk-linux/usr/bin/aarch64-oe-linux")
  set(CMAKE_C_COMPILER "${TOOLCHAIN_DIR}/aarch64-oe-linux-gcc")
  set(CMAKE_CXX_COMPILER "${TOOLCHAIN_DIR}/aarch64-oe-linux-g++")
  set(MYSYSROOT "/opt/AG215X/toolchain/sysroots/aarch64-oe-linux")

  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --sysroot=${MYSYSROOT}" CACHE INTERNAL "" FORCE)
  set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} --sysroot=${MYSYSROOT}" CACHE INTERNAL "" FORCE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --sysroot=${MYSYSROOT}" CACHE INTERNAL "" FORCE)
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} --sysroot=${MYSYSROOT}" CACHE INTERNAL "" FORCE)
  set(CMAKE_FIND_ROOT_PATH "${MYSYSROOT}")
endif()
######################################################################################################
set(PRJ_NAME ModuleXXX)
SET(CMAKE_SYSTEM_NAME Linux)
project (ModuleXXX)
# compiler/linker flags
set(CMAKE_VERBOSE_MAKEFILE on)

OPTION(USE_FILE "Set to OFF to disable file logging" OFF )
message(STATUS "USE_FILE is set to value: ${USE_FILE}")

OPTION(USE_CONSOLE "Set to OFF to disable console logging" OFF )
message(STATUS "USE_CONSOLE is set to value: ${USE_CONSOLE}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${LIBHEBI_CROSS_GCC_TOOLCHAIN_ARG}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -g -rdynamic -ldl")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -Wall -O0 -std=c11 -D_GLIBC_USE_NANOSLEEP -DLINUX")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LIBHEBI_CROSS_GCC_TOOLCHAIN_ARG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -O0 -std=c++11 -D_GLIBCXX_USE_NANOSLEEP -DLINUX")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -rdynamic -ldl")

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

include_directories(
    src
    src-gen
    ${BOOST_INCLUDE_DIR}
    ${CORE_RUNTIME_INCLUDE_DIR}
    ${SOMEIP_RUNTIME_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIR}
)

link_directories(
    ${BOOST_LINK_DIR}
    # ${COMMONAPI_LINK_DIR}
)

# Source Files
set(PRJ_SRC_PATH src)
set(PRJ_NAME_CLIENT ${PRJ_NAME}Client)
set(PRJ_NAME_SERVICE ${PRJ_NAME}Service)
# Application
FILE(GLOB PRJ_PROXY_GEN_SRCS src-gen/v0/commonapi/examples/*.cpp)

add_library(${PRJ_NAME_CLIENT}If SHARED  ${PRJ_SRC_PATH}/${PRJ_NAME_CLIENT}Impl.cpp ${PRJ_PROXY_GEN_SRCS})
# target_link_libraries(${PRJ_NAME_CLIENT}If CommonAPI)
# target_link_libraries(${PRJ_NAME_CLIENT}If CommonAPI-SomeIP)
# target_link_libraries(${PRJ_NAME_CLIENT}If vsomeip3)

add_library(${PRJ_NAME_SERVICE}If SHARED ${PRJ_SRC_PATH}/${PRJ_NAME_SERVICE}Impl.cpp ${PRJ_PROXY_GEN_SRCS})
# target_link_libraries(${PRJ_NAME_SERVICE}If CommonAPI)
# target_link_libraries(${PRJ_NAME_SERVICE}If CommonAPI-SomeIP)
# target_link_libraries(${PRJ_NAME_SERVICE}If vsomeip3)