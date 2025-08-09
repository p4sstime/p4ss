block()
if (${IS_LINUX})
	set(PLAT_EXE_NAME "linux64" CACHE INTERNAL "")
elseif (${IS_WINDOWS})
	set(PLAT_EXE_NAME "win64" CACHE INTERNAL "")
else()
	set(PLAT_EXE_NAME "unknown" CACHE INTERNAL "")
endif()

# Ensure the output of the executable is `game/`.
foreach(CONFIG_TYPE ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER "${CONFIG_TYPE}" CONFIG_TYPE_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} "${OUTBINDIR}")
endforeach()

add_executable(p4ss_launcher WIN32
"${SRCDIR}/launcher_main/main.cpp"
)

if(${IS_LINUX})
target_link_libraries(p4ss_launcher SDL2)
endif()

# Why valve?
target_link_options(p4ss_launcher PRIVATE
  "-Wl,--wrap=fopen"
  "-Wl,--wrap=fopen64"
)

set_target_properties(p4ss_launcher PROPERTIES 
	OUTPUT_NAME "p4ss_${PLAT_EXE_NAME}"
	RUNTIME_OUTPUT_DIRECTORY "${OUTBINDIR}"
)
if (${MOD_LAUNCHER})
	target_compile_definitions(p4ss_launcher PRIVATE
	MOD_LAUNCHER
	"MOD_APPID=3554290"
	)

endif()

if (${IS_WINDOWS})
	if (${MOD_LAUNCHER})
	target_sources(p4ss_launcher
	${SRCDIR}/launcher_main/launcher_main_mod_tf.rc
	)
	else()

	endif()
endif()
# For some reason this is included in Valve's VPC script.
target_compile_definitions(p4ss_launcher PRIVATE
FRAME_POINTER_OMISSION_DISABLED
)
endblock()