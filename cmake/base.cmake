# base.cmake
# This is CTRL+C CTRL+V'd from https://github.com/Spirrwell/source-sdk-2013-cmake/blob/master/mp/_cmake_scripts/base.cmake
# Thanks in advance lol


# NOTE: We use 0 or 1 so we can use these more easily in generator expressions
# Initialize them with default values that we then set later

set(IS_WINDOWS 0)
set(IS_LINUX 0)
set(IS_OSX 0)
set(IS_POSIX 0)

set(IS_XCODE 0)
set(IS_SOURCESDK 1)

if (WIN32)
	set(IS_WINDOWS 1)
endif()

if (UNIX AND NOT APPLE)
	set(IS_LINUX 1)
endif()

if (APPLE)
	set(IS_OSX 1)
	if (${CMAKE_GENERATOR} STREQUAL "Xcode")
		set(IS_XCODE 1)
	endif()
endif()

if (UNIX)
	set(IS_POSIX 1)
endif()

#$Macro PLATSUBDIR	"\."	[$WIN32]
#$Macro PLATSUBDIR	"\x64"	[$WIN64]
#$Macro PLATSUBDIR	"\."	[$X360]
#$Macro PLATSUBDIR	"\linux32" [$LINUX32]
#$Macro PLATSUBDIR	"\linux64" [$LINUX64]
#$Macro PLATSUBDIR	"\osx32" [$OSX32]

if (${IS_WINDOWS})
	set(_DLL_EXT ".dll")
	set(STATIC_LIB_EXT ".lib")
	set(IMPLIB_EXT ".lib")
	set(PLATSUBDIR /x64)
elseif (${IS_OSX})
	set(_DLL_EXT ".dylib")
	set(STATIC_LIB_EXT ".a")
	set(IMPLIB_EXT ".dylib")
	set(PLATSUBDIR /.)
elseif(${IS_LINUX})
	set(_DLL_EXT ".so")
	set(STATIC_LIB_EXT ".a")
	set(IMPLIB_EXT ".so")
	set(PLATSUBDIR /linux64)
endif()

set(OUTBINDIR	"${SRCDIR}/../game")
option(RETAIL "Build in retail mode" OFF)
option(STAGING_ONLY "Staging only" OFF)

set(RAD_TELEMETRY_DISABLED ${IS_SOURCESDK})
set(TF_BETA 0)
set(BUILD_REPLAY 0)
set(DEDICATED 0)

add_compile_definitions(
	$<$<BOOL:${RETAIL}>:_RETAIL>
	$<$<BOOL:${STAGING_ONLY}>:STAGING_ONLY>
	$<${TF_BETA}:TF_BETA>
	$<${RAD_TELEMETRY_DISABLED}:RAD_TELEMETRY_DISABLED>
	_DLL_EXT=${_DLL_EXT}
	FRAME_POINTER_OMISSION_DISABLED
)