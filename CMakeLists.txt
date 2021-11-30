# To compile and run:
#
#   mkdir build
#   cd build
#   cmake ..
#   make
#   make test
#

#-------------------------------------------------------------------------------
# get the version
#-------------------------------------------------------------------------------

# cmake 3.13 is preferred.
cmake_minimum_required ( VERSION 3.1 )

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

# version of Tetris
set ( TETRIS_VERSION_MAJOR 0 )
set ( TETRIS_VERSION_MINOR 0 )
set ( TETRIS_VERSION_SUB   1 )

project ( tetris
	VERSION "${TETRIS_VERSION_MAJOR}.${TETRIS_VERSION_MINOR}.${TETRIS_VERSION_SUB}" )

#-------------------------------------------------------------------------------
# code coverage and build type
#-------------------------------------------------------------------------------

if ( "${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	if ( COVERAGE )
                message ( STATUS "============== Code coverage enabled ===============" )
		set ( CMAKE_BUILD_TYPE Debug )
		include ( CodeCoverage )


		append_coverage_compiler_flags ( )

		# turn off optimization for non-skewed coverage reports
		set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0" )
		set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0" )

		setup_target_for_coverage_lcov (
			NAME test_coverage
			EXECUTABLE ctest
			DEPENDENCIES ${PROJECT_NAME}
			BASE_DIRECTORY "."
			NO_DEMANGLE TRUE
		)
	endif ( )
endif ( )

#-------------------------------------------------------------------------------
# determine build type
#-------------------------------------------------------------------------------

# For development only, not for end-users:
set ( CMAKE_BUILD_TYPE Debug )

if ( NOT CMAKE_BUILD_TYPE )
    set ( CMAKE_BUILD_TYPE Release )
endif ( )

#-------------------------------------------------------------------------------
# report status
#-------------------------------------------------------------------------------

message ( STATUS "CMAKE build type:          " ${CMAKE_BUILD_TYPE} )
message ( STATUS "CMAKE source directory:    " ${CMAKE_SOURCE_DIR} )
message ( STATUS "CMAKE build directory:     " ${CMAKE_BINARY_DIR} )

if ( ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message ( STATUS "CMAKE C Flags debug:       " ${CMAKE_C_FLAGS_DEBUG} )
else ( )
    message ( STATUS "CMAKE C Flags release:     " ${CMAKE_C_FLAGS_RELEASE} )
endif ( )

message ( STATUS "CMAKE compiler ID:         " ${CMAKE_C_COMPILER_ID} )

#-------------------------------------------------------------------------------
# compiler options
#-------------------------------------------------------------------------------

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

if ( "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" )
    # options for clang
    set ( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -std=c11 " )
endif ( )

if ( ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set ( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}" )
else ( )
    set ( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}" )
endif ( )

#-------------------------------------------------------------------------------
# print final C flags
#-------------------------------------------------------------------------------

message ( STATUS "CMAKE C flags: " ${CMAKE_C_FLAGS} )

#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

enable_testing()

add_subdirectory(src)

