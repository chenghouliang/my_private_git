cmake_minimum_required(VERSION 2.8)
set(PRJ_NAME ModuleXXX)
SET(CMAKE_SYSTEM_NAME Linux)
project (ModuleXXX)
######################################################################################################
set(TARGET "AG550")

if("${TARGET}" STREQUAL "AG550")
  set(TOOLCHAIN_DIR "/opt/AG55X/ql-ag550qcn-le20-gcc820-v1-toolchain/gcc/usr/bin/arm-oe-linux")
  set(CMAKE_C_COMPILER "${TOOLCHAIN_DIR}/arm-oe-linux-gcc")
  set(CMAKE_CXX_COMPILER "${TOOLCHAIN_DIR}/arm-oe-linux-g++")
  set(MYSYSROOT "/opt/AG55X/ql-ol-extsdk-ag550qcnabr03a10m8g_ocpu/ql-sysroots")

  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --sysroot=${MYSYSROOT} -march=armv7-a -mfpu=neon -mfloat-abi=hard" CACHE INTERNAL "" FORCE)
  set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} --sysroot=${MYSYSROOT}" CACHE INTERNAL "" FORCE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --sysroot=${MYSYSROOT}  -march=armv7-a -mfpu=neon -mfloat-abi=hard" CACHE INTERNAL "" FORCE)
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} --sysroot=${MYSYSROOT}" CACHE INTERNAL "" FORCE)
  set(CMAKE_FIND_ROOT_PATH "${MYSYSROOT}")

  set(COMMONAPI_LINK_DIR "/home/chenghl/AG550/libDirCommonAPI_AG550/commonapi")
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

  set(COMMONAPI_LINK_DIR "/home/chenghl/AG215S/libDirCommonAPI_AG215S/commonapi")
  set(BOOST_LINK_DIR "/home/chenghl/AG215S/libDirCommonAPI_AG215S/boost_1_72")
endif()
######################################################################################################

# compiler/linker flags
set(CMAKE_VERBOSE_MAKEFILE on)

OPTION(USE_FILE "Set to OFF to disable file logging" OFF )
message(STATUS "USE_FILE is set to value: ${USE_FILE}")

OPTION(USE_CONSOLE "Set to OFF to disable console logging" OFF )
message(STATUS "USE_CONSOLE is set to value: ${USE_CONSOLE}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${LIBHEBI_CROSS_GCC_TOOLCHAIN_ARG}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -Wall -O0 -std=c11 -D_GLIBC_USE_NANOSLEEP -DLINUX")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -g -rdynamic -ldl")
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
    ../src
)

link_directories(
    ../../build
    ${BOOST_LINK_DIR}
    ${COMMONAPI_LINK_DIR}
 )

# Application
set(PRJ_CLIENT_SRCS_A ModuleXXXClientModuleA.c)
set(PRJ_CLIENT_SRCS_B ModuleXXXClientModuleB.c)
set(PRJ_SERVICE_SRCS ModuleXXXService.c)

#Build Client
add_executable(ModuleXXXClientModuleA ${PRJ_CLIENT_SRCS_A})
target_link_libraries(ModuleXXXClientModuleA CommonAPI)
target_link_libraries(ModuleXXXClientModuleA CommonAPI-SomeIP)
target_link_libraries(ModuleXXXClientModuleA vsomeip3)
target_link_libraries(ModuleXXXClientModuleA boost_system)
target_link_libraries(ModuleXXXClientModuleA boost_thread)
target_link_libraries(ModuleXXXClientModuleA boost_filesystem)
target_link_libraries(ModuleXXXClientModuleA boost_atomic)
target_link_libraries(ModuleXXXClientModuleA ModuleXXXClientIf)

# Build Client
add_executable(ModuleXXXClientModuleB ${PRJ_CLIENT_SRCS_B})
target_link_libraries(ModuleXXXClientModuleB CommonAPI)
target_link_libraries(ModuleXXXClientModuleB CommonAPI-SomeIP)
target_link_libraries(ModuleXXXClientModuleB vsomeip3)
target_link_libraries(ModuleXXXClientModuleB boost_system)
target_link_libraries(ModuleXXXClientModuleB boost_thread)
target_link_libraries(ModuleXXXClientModuleB boost_filesystem)
target_link_libraries(ModuleXXXClientModuleB boost_atomic)
target_link_libraries(ModuleXXXClientModuleB ModuleXXXClientIf)

# Build service
add_executable(ModuleXXXService ${PRJ_SERVICE_SRCS})
target_link_libraries(ModuleXXXService CommonAPI)
target_link_libraries(ModuleXXXService CommonAPI-SomeIP)
target_link_libraries(ModuleXXXService vsomeip3)
target_link_libraries(ModuleXXXService boost_system)
target_link_libraries(ModuleXXXService boost_thread)
target_link_libraries(ModuleXXXService boost_filesystem)
target_link_libraries(ModuleXXXService boost_atomic)
target_link_libraries(ModuleXXXService ModuleXXXServiceIf)
