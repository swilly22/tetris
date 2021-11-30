#include "board.h"
#include "screen.h"
#include "tetris.h"
#include <stdlib.h>
#include <string.h>

#define ROW(board, row) (board + (BOARD_WIDTH * (row)))

static bool _row_full
(
	bool *row
) {
	bool full = true ;

	for (int i = 0 ; i < BOARD_WIDTH ; i++)
	{
		full &= row[i] ;
	}

	return full ;
}

static bool _shape_in_bounds
(
	const Shape *shape  // shape to validate
) {

	// make sure shape is within board bounds
	for (uint i = 0 ; i < shape->n_blocks ; i++)
	{
		int x = shape->blocks[i].x ;
		int y = shape->blocks[i].y ;
		
		if (x < 0            ||
		    x >= BOARD_WIDTH ||
		    y < 0
		)
		{
			return false ;
		}
	}

	return true ;
}

// creates a new board
Board Board_New (void)
{
	// add 1 to BOARD_HEIGHT as a hidden row from which shapes enter
	Board board = calloc (BOARD_WIDTH * (BOARD_HEIGHT + 1), sizeof (bool)) ;
	assert (board != NULL) ;
	return board ;
}

// checks if current shape position intersects with any
// board's blocks
bool Board_Intersect
(
	const Board board,   // board to intersect against
	const Shape *shape   // shape to intersect with
) {
	ASSERT_NOT_NULL  (board) ;
	ASSERT_NOT_NULL  (shape) ;
	
	bool intersects = true ;

	if (_shape_in_bounds (shape))
	{
		intersects = false ;
		for (int i = 0 ; i < shape->n_blocks ; i++)
		{
			uint x = shape->blocks[i].x ;
			uint y = shape->blocks[i].y ;

			intersects |= ROW (board, y)[x] ;
		}
	}
	
	return intersects ;
}

// adds shape to board
void Board_SetShape
(
	Board board,        // board to add shape to
	const Shape *shape  // shape added
) {
	ASSERT_NOT_NULL  (board) ;
	ASSERT_NOT_NULL  (shape) ;
	_shape_in_bounds (shape) ;

	for (uint i = 0 ; i < shape->n_blocks ; i++)
	{
		uint x = shape->blocks[i].x ;
		uint y = shape->blocks[i].y ;

		// block must be unset
		assert (ROW (board, y)[x] == false) ;
		ROW (board, y)[x] = true ;
	}
}

void Board_RemoveShape
(
	Board board,        // board from which shape is removed
	const Shape *shape  // shape to remove
) {
	ASSERT_NOT_NULL  (board) ;
	ASSERT_NOT_NULL  (shape) ;
	_shape_in_bounds (shape) ;

	// unset each shape block from board
	for (uint i = 0 ; i < shape->n_blocks ; i++)
	{
		uint x = shape->blocks[i].x ;
		uint y = shape->blocks[i].y ;

		// block must be set
		assert (ROW (board, y)[x] == true) ;
		ROW (board, y)[x] = false ;
	}
}

// clears rows where all columns are set
// returns the number of rows cleared
int Board_ClearFullRows
(
	Board board         // board to clear rows from
) {
	uint n   = 0 ; // number of full rows
	uint row = 0 ; // full row lowest index

	// search for complete rows
	for (uint row = 0 ; row < BOARD_HEIGHT ; row++)
	{
		if (_row_full (ROW (board, row)))
		{
			// consume all consecutive complete rows
			int i = 0 ;
			while (_row_full (ROW (board, row + i)))
			{
				i++ ;
				n++ ;
			}

			// shift down `i` rows
			memcpy (ROW (board, row), ROW (board, row + i), BOARD_WIDTH * (BOARD_HEIGHT - row - i)) ;
			// clear top i rows
			memset (ROW (board, BOARD_HEIGHT - i), 0, BOARD_WIDTH * i) ;
		}
	}

	return n ;
}

void Board_Print
(
	const Board board   // board to print
) {
	ASSERT_NOT_NULL (board) ;

	SCREEN_GOTO (0, 0) ; 

	// print board
	for (int row = BOARD_HEIGHT ; row >= 0 ; row--)
	{
		for (int col = 0 ; col < BOARD_WIDTH ; col++)
		{
			if (ROW(board, row)[col])
			{
				// entry is SET
				printf ("*") ;
			}
			else
			{
				// entry is CLEAR
				printf (".") ;
			}
		}
		printf ("\n") ;
	}
}

void Board_Free
(
	Board *board
) {
	RETURN_IF_NULL (board) ;

	free (*board) ;
	*board = NULL ;
}

