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

  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
  set(BOOST_ROOT "/home/chenghl/AG550/boost_1_72_0/obj")
  set(vsomeip3_DIR "/home/chenghl/AG550/vsomeip/build")
  set(CommonAPI_DIR "/home/chenghl/AG550/capicxx-core-runtime/build")
  set(CommonAPI-SomeIP_DIR "/home/chenghl/AG550/capicxx-someip-runtime/build")
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

  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
  set(BOOST_ROOT "/opt/AG215X/package/usr")
  set(vsomeip3_DIR "/home/chenghl/AG215S/vsomeip/build")
  set(CommonAPI_DIR "/home/chenghl/AG215S/capicxx-core-runtime/build")
  set(CommonAPI-SomeIP_DIR "/home/chenghl/AG215S/capicxx-someip-runtime/build")
else()
  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
  set(vsomeip3_DIR "/home/chenghl/CommonAPI/vsomeip/build")
  set(CommonAPI_DIR "/home/chenghl/CommonAPI/capicxx-core-runtime/build")
  set(CommonAPI-SomeIP_DIR "/home/chenghl/CommonAPI/capicxx-someip-runtime/build")
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
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -Wall -O0 -std=c11 -D_GLIBC_USE_NANOSLEEP -DLINUX -Wl,-rpath=./:./lib")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -Wall -O0 -std=c11 -D_GLIBC_USE_NANOSLEEP -DLINUX -Wl,-rpath=${vsomeip3_DIR}:${CommonAPI_DIR}:${CommonAPI-SomeIP_DIR}")
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

if ("${USE_INSTALLED_COMMONAPI}" STREQUAL "ON")
   FIND_PACKAGE(CommonAPI 3.2.0 REQUIRED CONFIG NO_CMAKE_PACKAGE_REGISTRY)
else()
  FIND_PACKAGE(CommonAPI 3.2.0 REQUIRED CONFIG NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH)
endif()

# CommonAPI
include(FindPkgConfig)
find_package (CommonAPI-SomeIP 3.2.0 REQUIRED)
find_package (vsomeip3 3.1.20 REQUIRED)
find_package( Boost 1.54 COMPONENTS system thread log REQUIRED )

message(STATUS "CommonAPI_CONSIDERED_CONFIGS: ${CommonAPI_CONSIDERED_CONFIGS}")
message(STATUS "COMMONAPI_INCLUDE_DIRS: ${COMMONAPI_INCLUDE_DIRS}")
message(STATUS "COMMONAPI_SOMEIP_INCLUDE_DIRS: ${COMMONAPI_SOMEIP_INCLUDE_DIRS}")
message(STATUS "Boost_INCLUDE_DIR: ${Boost_INCLUDE_DIR}")
include_directories(
    ../src
    ${COMMONAPI_INCLUDE_DIRS}
    ${COMMONAPI_SOMEIP_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIR}
)

link_directories(
     ../../build
     ${Boost_LIBRARY_DIR}
     ${vsomeip3_DIR}
     ${CommonAPI_DIR}
     ${CommonAPI-SomeIP_DIR}
 )

if (MSVC)
 set(LINK_LIBRARIES CommonAPI)
else()
 set(LINK_LIBRARIES -Wl,--as-needed CommonAPI)
endif()

# Application
set(PRJ_CLIENT_SRCS_A ModuleXXXClientModuleA.c)
set(PRJ_CLIENT_SRCS_B ModuleXXXClientModuleB.c)
set(PRJ_SERVICE_SRCS ModuleXXXService.c)

#Build Client
add_executable(ModuleXXXClientModuleA ${PRJ_CLIENT_SRCS_A})
target_link_libraries(ModuleXXXClientModuleA CommonAPI)
target_link_libraries(ModuleXXXClientModuleA CommonAPI-SomeIP)
target_link_libraries(ModuleXXXClientModuleA vsomeip3)
target_link_libraries(ModuleXXXClientModuleA libModuleXXXClientIf.so)

# Build Client
add_executable(ModuleXXXClientModuleB ${PRJ_CLIENT_SRCS_B})
target_link_libraries(ModuleXXXClientModuleB CommonAPI)
target_link_libraries(ModuleXXXClientModuleB CommonAPI-SomeIP)
target_link_libraries(ModuleXXXClientModuleB vsomeip3)
target_link_libraries(ModuleXXXClientModuleB libModuleXXXClientIf.so)

# Build service
add_executable(ModuleXXXService ${PRJ_SERVICE_SRCS})
target_link_libraries(ModuleXXXService CommonAPI)
target_link_libraries(ModuleXXXService CommonAPI-SomeIP)
target_link_libraries(ModuleXXXService vsomeip3)
target_link_libraries(ModuleXXXService libModuleXXXServiceIf.so)
