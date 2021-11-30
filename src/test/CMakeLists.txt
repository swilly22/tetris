#-------------------------------------------------------------------------------
# tetris/src/test/CMakeLists.txt:  cmake script for tetris/src/test
#-------------------------------------------------------------------------------

include_directories ( ${CMAKE_SOURCE_DIR}/src/test/include )

# Uncomment this line for for development only, not for end-users:
set ( CMAKE_BUILD_TYPE Debug )
if ( ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set ( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}" )
else ( )
    set ( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
endif ( )

#-------------------------------------------------------------------------------
# This will only build tests from files with the name "test_*.c"
#-------------------------------------------------------------------------------

file ( GLOB TEST_SOURCES LIST_DIRECTORIES false test_*.c )
foreach ( testsourcefile ${TEST_SOURCES} )
	get_filename_component ( justname ${testsourcefile} NAME )
	string ( REPLACE ".c" "" testname ${justname} )
	message ( "Adding: ${testname}" )
	add_executable ( ${testname} ${testsourcefile} )
	target_link_libraries( ${testname} tetris_static )
	string ( REPLACE "test_" "ctest_" ctestname ${testname} )
	add_test ( ${ctestname} ${testname} )
endforeach( testsourcefile ${TEST_SOURCES} )

