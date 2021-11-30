#-------------------------------------------------------------------------------
# TETRIS/src/CMakeLists.txt:  cmake script for TETRIS/src
#-------------------------------------------------------------------------------

file ( GLOB TETRIS_SOURCES "./*.c" "./shapes/*.c" )

add_subdirectory ( test )
add_executable ( tetris ${TETRIS_SOURCES} )

#-------------------------------------------------------------------------------
# static tetris library properties
#-------------------------------------------------------------------------------

add_library ( tetris_static STATIC ${TETRIS_SOURCES} )
SET_TARGET_PROPERTIES ( tetris_static PROPERTIES 
	OUTPUT_NAME tetris
	C_STANDARD_REQUIRED 11 )
set_property ( TARGET tetris_static PROPERTY C_STANDARD 11 )


#-------------------------------------------------------------------------------
# Tetrix executable
#-------------------------------------------------------------------------------
add_executable ( tetris_exec main.c )
target_link_libraries( tetris_exec tetris_static )

