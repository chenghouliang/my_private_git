cmake_minimum_required(VERSION 2.8)
######################################################################################################
set(TARGET "PC")

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
endif()
######################################################################################################
set(PRJ_NAME ModuleXXX)
set(CMAKE_VERBOSE_MAKEFILE on)

OPTION(USE_FILE "Set to OFF to disable file logging" OFF )
message(STATUS "USE_FILE is set to value: ${USE_FILE}")

OPTION(USE_CONSOLE "Set to OFF to disable console logging" OFF )
message(STATUS "USE_CONSOLE is set to value: ${USE_CONSOLE}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${LIBHEBI_CROSS_GCC_TOOLCHAIN_ARG}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -g -rdynamic -ldl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LIBHEBI_CROSS_GCC_TOOLCHAIN_ARG}")
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

if (MSVC)
# Visual C++ is not always sure whether he is really C++
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_CRT_SECURE_NO_WARNINGS /EHsc /wd\\\"4503\\\"")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS /wd\\\"4503\\\"")
else()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -Wall -O0 -std=c11 -D_GLIBC_USE_NANOSLEEP -DLINUX")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -O0 -std=c++11 -D_GLIBCXX_USE_NANOSLEEP -DLINUX")
endif()

message(STATUS "Compiler options: ${CMAKE_CXX_FLAGS}") 

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
       "Choose the type of build, options are: Debug Release." FORCE)
endif(NOT CMAKE_BUILD_TYPE)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# CommonAPI
###############################################################################

include_directories(
    ../src
)
link_directories(
     ../../build
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

# Build Client
add_executable(ModuleXXXClientModuleA ${PRJ_CLIENT_SRCS_A})
target_link_libraries(ModuleXXXClientModuleA libModuleXXXClientIf.so)

# Build Client
add_executable(ModuleXXXClientModuleB ${PRJ_CLIENT_SRCS_B})
target_link_libraries(ModuleXXXClientModuleB libModuleXXXClientIf.so)

# Build service
add_executable(ModuleXXXService ${PRJ_SERVICE_SRCS})
target_link_libraries(ModuleXXXService libModuleXXXServiceIf.so)
