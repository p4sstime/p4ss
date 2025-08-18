cmake_minimum_required(VERSION 3.12...4.0 FATAL_ERROR)

project(
  PASSFortress
  VERSION 0.1.0
  LANGUAGES C CXX
)

set(CMAKE_GENERATOR_PLATFORM "x64")

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

if(${IS_WINDOWS})
set(CMAKE_C_STANDARD 11)
else()
# For some reason, Valve doesn't specify a C std in their code.
# I'm setting this as the current default for gcc (std=gnu17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS TRUE)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_compile_definitions(
  PLATFORM_64BITS
  CMAKE
)

if(${IS_LINUX})
  set(CMAKE_C_COMPILER /usr/bin/gcc CACHE STRING "Compiler" FORCE)
  set(CMAKE_CXX_COMPILER /usr/bin/g++ CACHE STRING "CXX Compiler" FORCE)
  link_libraries(m dl pthread uuid)

  add_compile_definitions(
    stricmp=strcasecmp
    _snprintf=snprintf
    _vsnprintf=vsnprintf
    #_DLL_EXT=so # this is previously set in base.cmake
    GNUC
    NO_HOOK_MALLOC
    FILE_OFFSET_BITS=64
    VPROF_LEVEL=1
    LINUX _LINUX POSIX _POSIX
    USE_SDL
  )
  remove_definitions(
    PROTECTED_THINGS_ENABLE
    sprintf
    strncpy
  )
  link_directories(
    /usr/include/SDL2
  )
  set(NINJA_ARCH_FLAGS "-march=nocona -march=core2")
  set(NINJA_WARN_FLAGS_C
    "-Wall \
    -Wno-multichar -Wno-write-strings -Wno-unused-variable -Wno-unused-function -Winvalid-pch -Wswitch \
    -Wno-sign-compare -Wno-nonnull-compare -Wno-ignored-attributes -Wno-misleading-indentation -Wno-unused-but-set-variable -Wno-unused-local-typedefs \
    -Wno-switch -Wno-parentheses \
    -Wno-unknown-pragmas -Wno-unused-parameter -Wno-unused-value \
	  -Wno-comment \
    -Wno-float-equal -Werror=return-type \
    -Wformat -Wformat-security"
  )
  # -Wno-mismatched-new-delete excluded since it doesn't work in Sniper container
  # and adds to the compiler error spew for no tangible benefit.
  # If we're seriously getting mismatched-new-delete warns on newer compilers,
  # please fix them instead of killing the warning
  set(NINJA_WARN_FLAGS_CXX 
    "-Wno-overloaded-virtual -Wno-placement-new -Wno-c++20-compat \
     -Wno-class-memaccess -Wno-conversion-null -Wno-invalid-offsetof -Wno-reorder"
  )
  
  if (${DEVELOPMENT_ONLY})
    set(NINJA_C_DEV_FLAGS "-fstack-protector -fcf-protection")
    set(NINJA_STACK_OPT_DEBUG "-fstack-clash-protection")
    set(NINJA_STACK_OPT_RELEASE "-fstack-clash-protection -Wp,-D_FORTIFY_SOURCE=2")
  endif()

  set(NINJA_C_FLAGS "\
    ${NINJA_ARCH_FLAGS} ${NINJA_WARN_FLAGS_C} ${NINJA_C_DEV_FLAGS} \
    -fpch-preprocess -fvar-tracking-assignments \
    -fPIC -pipe \
    -fdiagnostics-color -fdiagnostics-show-option \
  ")
  set(NINJA_CXX_FLAGS "${NINJA_C_FLAGS} ${NINJA_WARN_FLAGS_CXX} -I/usr/include/freetype2")

  set(NINJA_OPTIMIZATION_DEBUG "-Og -ggdb3 $NINJA_STACK_OPT_DEBUG -fno-delete-null-pointer-checks")
  set(NINJA_OPTIMIZATION_RELEASE 
  "-O2 -g $NINJA_STACK_OPT_RELEASE -fno-strict-aliasing -ffast-math \
  -fno-omit-frame-pointer -fno-delete-null-pointer-checks -ftree-vectorize \
  -fpredictive-commoning -funswitch-loops"
  )

  set(CMAKE_C_FLAGS ${NINJA_C_FLAGS})
  set(CMAKE_CXX_FLAGS ${NINJA_CXX_FLAGS})
  set(CMAKE_C_FLAGS_DEBUG ${NINJA_OPTIMIZATION_DEBUG})
  set(CMAKE_CXX_FLAGS_DEBUG ${NINJA_OPTIMIZATION_DEBUG})
  set(CMAKE_C_FLAGS_RELEASE ${NINJA_OPTIMIZATION_RELEASE})
  set(CMAKE_CXX_FLAGS_RELEASE ${NINJA_OPTIMIZATION_RELEASE})
  # NINJA_COMMON_LINK_FLAGS
  add_link_options(
    # NINJA_PATHWRAP
    -Wl,--wrap=fopen -Wl,--wrap=freopen -Wl,--wrap=open    -Wl,--wrap=creat    -Wl,--wrap=access  -Wl,--wrap=__xstat
    -Wl,--wrap=stat  -Wl,--wrap=stat64  -Wl,--wrap=lstat   -Wl,--wrap=fopen64  -Wl,--wrap=open64  -Wl,--wrap=opendir 
    -Wl,--wrap=chmod -Wl,--wrap=chown   -Wl,--wrap=lchown  -Wl,--wrap=symlink  -Wl,--wrap=link    -Wl,--wrap=__lxstat64
    -Wl,--wrap=mknod -Wl,--wrap=utimes  -Wl,--wrap=unlink  -Wl,--wrap=rename   -Wl,--wrap=utime   -Wl,--wrap=__xstat64
    -Wl,--wrap=mount -Wl,--wrap=mkfifo  -Wl,--wrap=mkdir   -Wl,--wrap=rmdir    -Wl,--wrap=scandir -Wl,--wrap=realpath
    -Wl,--wrap=__lxstat

    -Wl,--build-id -Wl,-z,noexecstack
  )
endif()

include_directories(
  ${SRCDIR}/public
  ${SRCDIR}/public/tier0
  ${SRCDIR}/public/tier1
  ${SRCDIR}/common
)

if(${IS_WINDOWS})
  add_compile_definitions(
    COMPILER_MSVC
    PLATFORM_64BITS
    WIN64 _WIN64
    COMPILER_MSVC64
  )

  if(MSVC)
    add_compile_options(
    # /Gw is a VS 2013 option that puts global and static variables in individual sections so that the
		# linker can discard unreferenced data. When building @client /dota with linker optimizations this
		# reduces the client.dll size by about 1.14%. When linker optimizations are disabled this has no
		# effect. This option does not show up in the IDE so we need to add it in $AdditionalOptions.
		# http://blogs.msdn.com/b/vcblog/archive/2013/09/11/introducing-gw-compiler-switch.aspx
    "/Gw"
    # Compile with multiple processes
    /MP
    /Zc:inline
    /Zc:threadSafeInit-
    # Sets __cplusplus macro to accurate value
    # instead of the value for C++98
    /Zc:__cplusplus
    )
  endif()
endif()

include("cmake/launcher.cmake")
include("cmake/vgui_controls.cmake")
include("cmake/tier1.cmake")
