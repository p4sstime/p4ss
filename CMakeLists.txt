cmake_minimum_required(VERSION 3.12...4.0 FATAL_ERROR)

project(
  PASSFortress
  VERSION 0.1.0
  LANGUAGES C CXX
)

if(APPLE)
  message(FATAL_ERROR "OSX is not supported.")
endif()

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(FATAL_ERROR "Your platform architecture is not supported. Use a 64-bit platform")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# For some reason, checking if CMAKE_BUILD_TYPE is defined is unreliable
# So simply check if it's empty instead
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

set(SRCDIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(GAMEDIR "${CMAKE_CURRENT_LIST_DIR}/game")
set(THIRDPARTYDIR "${SRCDIR}/thirdparty")

include("cmake/base.cmake")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_compile_definitions(
  PLATFORM_64BITS
)
if(${IS_LINUX})

  link_libraries("dl")

  add_compile_definitions(
    stricmp=strcasecmp
    _snprintf=snprintf
    _vsnprintf=vsnprintf
    #_DLL_EXT=so # this is previously set in base.cmake
    GNUC
    LINUX
    _LINUX
    POSIX
    _POSIX
    USE_SDL
  )

  link_directories(
    /usr/include/SDL2
  )
endif()

include_directories(
  ${SRCDIR}/public
  ${SRCDIR}/public/tier0
  ${SRCDIR}/public/tier1
)

if(${IS_WINDOWS})
  add_compile_definitions(
    COMPILER_MSVC
  )

endif()

include("cmake/launcher.cmake")
include("cmake/vgui_controls.cmake")
