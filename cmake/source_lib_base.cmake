# Ensure the output of the executable is `OUTLIBDIR/` regardless of config.
foreach(CONFIG_TYPE ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER "${CONFIG_TYPE}" CONFIG_TYPE_UPPER)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${OUTLIBDIR})
endforeach()

add_link_options(
    ${project_ldflags}
    -Wl,--no-undefined
)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTLIBDIR})