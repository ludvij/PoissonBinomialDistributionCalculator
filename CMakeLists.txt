cmake_minimum_required(VERSION 3.31)
project(probcalc)


set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)


set(generator_config 
	$<$<CONFIG:Debug>:DEBUG>
	$<$<CONFIG:Release,MinSizeRel,RelWithDebugInfo>:RELEASE>
)

if(MSVC)
	SET(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
# SET(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()



set (bin_dir "${CMAKE_SOURCE_DIR}/bin")
set (output_dir "${bin_dir}/${CMAKE_SYSTEM_NAME}-$<CONFIG>")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${output_dir})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${output_dir})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${output_dir}/lib)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Lud_Utils)

add_subdirectory(probcalc)

set_target_properties(ludutils PROPERTIES FOLDER "Utiliy")