#include <tetris_test.h>
#include "../board.h"
#include "../shape.h"

//******************************************************************************

// utility function, return true if board[x,y] is set
static bool Board_IsSet
(
	Board board,  // board to query
	uint x,       // X coordinate
	uint y        // Y coordinate
) {
	// compute index
	uint idx = BOARD_WIDTH * y + x ;
	return board[idx] ;
}

static Board _Board_FromRawInput
(
	bool *input
) {

	// revese input
	bool row[BOARD_WIDTH] ;

	for (int i = 0 ; i < (BOARD_HEIGHT + 1) / 2 ; i ++)
	{
		int src = i ;
		int dest = BOARD_HEIGHT + 1 - i - 1 ;

		memcpy (row, input + (src * BOARD_WIDTH), BOARD_WIDTH) ;

		memcpy (input + (src * BOARD_WIDTH), input + (dest * BOARD_WIDTH), BOARD_WIDTH) ;

		memcpy (input + (dest * BOARD_WIDTH), row, BOARD_WIDTH) ;
	}

	return (Board) input ;
}

// return true if A and B have the same structure
// A[i,j] = B[i,j] for every i in BOARD_HEIGH and j in BOARD_WIDTH
static bool _Board_EQ
(
	const Board A,
	const Board B
) {
	int entries = BOARD_WIDTH * (BOARD_HEIGHT + 1) ;
	bool equal = true ;

	for (int i = 0 ; i < entries ; i++)
	{
		equal &= A[i] == B[i] ;
	}

	return equal ;
}

void setup (void)
{
	// seed random
	time_t t ;
	srand ((unsigned) time (&t)) ;
}

//******************************************************************************

void test_Board_New (void)
{
	setup () ;
	Board board = Board_New () ;

	TEST_CHECK (board != NULL) ;

	// board should be empty
	for (int i = 0 ; i < BOARD_WIDTH * (BOARD_HEIGHT + 1) ; i++)
	{
		TEST_CHECK (board[i] == 0) ;
	}

	// Board_Free should set its input to NULL
	Board_Free (&board) ;
	TEST_CHECK (board == NULL) ;

	// it is OK to call Board_Free on NULL
	Board_Free (&board) ;
	TEST_CHECK (board == NULL) ;
}

//******************************************************************************

void test_Board_SetShape (void)
{
	setup () ;

	Board board = Board_New () ;
	Shape *shapes[5] ;
	shapes[0] = I_New () ;
	shapes[1] = L_New () ;
	shapes[2] = O_New () ;
	shapes[3] = S_New () ;
	shapes[4] = T_New () ;

	for (int i = 0 ; i < 5 ; i++)
	{
		Shape *s = shapes[i] ;

		// board should be clear at shape's position
		for (int j = 0 ; j < s->n_blocks ; j++)
		{
			uint x = s->blocks[j].x ;
			uint y = s->blocks[j].y ;
			TEST_CHECK (Board_IsSet (board, x, y) == false) ;
		}

		Board_SetShape (board, s) ;

		// set I at its default position
		// Board_Print (board) ;
		// printf ("\n\n\n") ;
		for (int j = 0 ; j < s->n_blocks ; j++)
		{
			uint x = s->blocks[j].x ;
			uint y = s->blocks[j].y ;
			TEST_CHECK (Board_IsSet (board, x, y) == true) ;
		}
		
		Board_RemoveShape (board, s) ;

		// board should be clear at shape's position
		for (int j = 0 ; j < s->n_blocks ; j++)
		{
			uint x = s->blocks[j].x ;
			uint y = s->blocks[j].y ;
			TEST_CHECK (Board_IsSet (board, x, y) == false) ;
		}

		Shape_Free (&s) ;
	}

	Board_Free (&board) ;
}

//******************************************************************************

void test_Board_Intersect (void)
{
	setup () ;

	Board board = Board_New () ;
	Shape *shapes[5] ;
	shapes[0] = I_New () ;
	shapes[1] = L_New () ;
	shapes[2] = O_New () ;
	shapes[3] = S_New () ;
	shapes[4] = T_New () ;

	// create a single block shape
	Shape *block = NEW_SHAPE(1) ;

	for (int i = 0 ; i < 5 ; i++)
	{
		Shape *s = shapes[i] ;

		// intersect s with an empty board
		// s is at its starting position
		TEST_CHECK(Board_Intersect (board, s) == false) ;
		
		// place our single block shape at each of s blocks
		for (int j = 0 ; j < s->n_blocks ; j ++)
		{
			int x = s->blocks[j].x ;
			int y = s->blocks[j].y ;

			block->blocks[0] = (Point) {x,y} ;

			Board_SetShape (board, block) ;

			TEST_CHECK(Board_Intersect (board, s) == true) ;

			Board_RemoveShape (board, block) ;

			TEST_CHECK(Board_Intersect (board, s) == false) ;
		}

		// place block at the bottom left corner of the board
		block->blocks[0] = (Point) {0,0} ;
		Board_SetShape (board, block) ;

		TEST_CHECK(Board_Intersect (board, s) == false) ;

		Board_RemoveShape (board, block) ;
		Shape_Free (&s) ;
	}
	
	Board_Free (&board) ;
	Shape_Free (&block) ;
}

//******************************************************************************

void test_Board_IntersectBoarders (void)
{
	setup () ;

	Board board = Board_New () ;
	Shape *shapes[5] ;
	shapes[0] = I_New () ;
	shapes[1] = L_New () ;
	shapes[2] = O_New () ;
	shapes[3] = S_New () ;
	shapes[4] = T_New () ;

	for (uint i = 0 ; i < 5 ; i++)
	{
		Shape *s = shapes[i] ;

		// find shape rightmost, leftmost and lowest blocks
		int  lowest     =  s->blocks[0].y ;
		int  leftmost   =  s->blocks[0].x ;
		int  rightmost  =  s->blocks[0].x ;
		
		for (uint j = 0 ; j < s->n_blocks ; j++)
		{
			Point block = s->blocks[j] ;

			if (rightmost < block.x)
			{
				rightmost = block.x ;
			}
			
			if (leftmost > block.x)
			{
				leftmost = block.x ;
			}

			if (lowest > block.y)
			{
				lowest = block.y ;
			}
		}

		//--------------------------------------------------------------------------
		// right intersection
		//--------------------------------------------------------------------------

		// move shpe to board right border
		for ( int j = 0 ; j < BOARD_WIDTH - rightmost ; j++)
		{
			Shape_ShiftRight (s) ;
		}

		TEST_CHECK (Board_Intersect (board, s) == true) ;

		// restore shape to its original position
		for ( int j = 0 ; j < BOARD_WIDTH - rightmost ; j++)
		{
			Shape_ShiftLeft (s) ;
		}

		//--------------------------------------------------------------------------
		// left intersection
		//--------------------------------------------------------------------------

		// move shpe to board left border
		for ( int j = 0 ; j < BOARD_WIDTH - leftmost ; j++)
		{
			Shape_ShiftLeft (s) ;
		}

		TEST_CHECK (Board_Intersect (board, s) == true) ;

		// restore shape to its original position
		for ( int j = 0 ; j < BOARD_WIDTH - leftmost ; j++)
		{
			Shape_ShiftRight (s) ;
		}

		//--------------------------------------------------------------------------
		// bottom intersection
		//--------------------------------------------------------------------------

		// move shpe to board bottom border
		for ( int j = lowest ; j >= 0 ; j--)
		{
			Shape_PushDown (s) ;
		}

		TEST_CHECK (Board_Intersect (board, s) == true) ;

		// restore shape to its original position
		for ( uint j = 0 ; j <= lowest ; j++)
		{
			Shape_PushUp (s) ;
		}

		Shape_Free (&s) ;
	}
	
	Board_Free (&board) ;
}

//******************************************************************************

void test_Board_ClearFullRows (void)
{
	int rows_cleared = 0 ; // number of rows cleared

	//--------------------------------------------------------------------------
	bool single_row[BOARD_WIDTH * (BOARD_HEIGHT + 1)] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	} ;

	bool single_row_expected[BOARD_WIDTH * (BOARD_HEIGHT + 1)] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	} ;

	Board  input_board     =  _Board_FromRawInput  (single_row)           ;
	Board  expected_board  =  _Board_FromRawInput  (single_row_expected)  ;

	rows_cleared = Board_ClearFullRows (input_board) ;
	TEST_CHECK (rows_cleared == 1) ;
	TEST_CHECK (_Board_EQ (input_board, expected_board)) ;

	//--------------------------------------------------------------------------

	bool two_rows[BOARD_WIDTH * (BOARD_HEIGHT + 1)] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	} ;

	bool expected_two_rows[BOARD_WIDTH * (BOARD_HEIGHT + 1)] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	} ;

	input_board     =  _Board_FromRawInput  (two_rows)           ;
	expected_board  =  _Board_FromRawInput  (expected_two_rows)  ;

	rows_cleared = Board_ClearFullRows (input_board) ;
	TEST_CHECK (rows_cleared == 2) ;
	TEST_CHECK (_Board_EQ (input_board, expected_board)) ;

	//--------------------------------------------------------------------------

	bool three_rows[BOARD_WIDTH * (BOARD_HEIGHT + 1)] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	} ;

	bool expected_three_rows[BOARD_WIDTH * (BOARD_HEIGHT + 1)] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	} ;

	input_board     =  _Board_FromRawInput  (three_rows)           ;
	expected_board  =  _Board_FromRawInput  (expected_three_rows)  ;

	rows_cleared = Board_ClearFullRows (input_board) ;
	TEST_CHECK (rows_cleared == 3) ;
	TEST_CHECK (_Board_EQ (input_board, expected_board)) ;

	//--------------------------------------------------------------------------

	bool triangle[BOARD_WIDTH * (BOARD_HEIGHT + 1)] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
		0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
		0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	} ;

	bool expected_triangle[BOARD_WIDTH * (BOARD_HEIGHT + 1)] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
		0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
		0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	} ;

	input_board     =  _Board_FromRawInput  (triangle)           ;
	expected_board  =  _Board_FromRawInput  (expected_triangle)  ;

	rows_cleared = Board_ClearFullRows (input_board) ;
	TEST_CHECK (rows_cleared == 2) ;
	TEST_CHECK (_Board_EQ (input_board, expected_board)) ;

	//--------------------------------------------------------------------------

	bool rectangle[BOARD_WIDTH * (BOARD_HEIGHT + 1)] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0, 1, 0
	} ;

	bool expected_rectangle[BOARD_WIDTH * (BOARD_HEIGHT + 1)] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
		1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0, 1, 0
	} ;

	input_board     =  _Board_FromRawInput  (rectangle)           ;
	expected_board  =  _Board_FromRawInput  (expected_rectangle)  ;

	rows_cleared = Board_ClearFullRows (input_board) ;
	TEST_CHECK (rows_cleared == 1) ;
	TEST_CHECK (_Board_EQ (input_board, expected_board)) ;

	//--------------------------------------------------------------------------

	bool space[BOARD_WIDTH * (BOARD_HEIGHT + 1)] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	} ;

	bool expected_space[BOARD_WIDTH * (BOARD_HEIGHT + 1)] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0, 1, 1, 1, 1
	} ;

	input_board     =  _Board_FromRawInput  (space)           ;
	expected_board  =  _Board_FromRawInput  (expected_space)  ;

	rows_cleared = Board_ClearFullRows (input_board) ;
	TEST_CHECK (rows_cleared == 2) ;
	TEST_CHECK (_Board_EQ (input_board, expected_board)) ;
}

//******************************************************************************

TEST_LIST = {
	{"Board_New", test_Board_New},
	{"Board_SetShape", test_Board_SetShape},
	{"Board_Intersect", test_Board_Intersect},
	{"Board_IntersectBoarders", test_Board_IntersectBoarders},
	{"Board_ClearFullRows", test_Board_ClearFullRows},
	{NULL, NULL}
} ;

