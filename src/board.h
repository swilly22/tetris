#ifndef  __BOARD__H_
#define  __BOARD__H_

#include <stdbool.h>
#include "./shape.h"

// board is a two dimensional array
typedef bool *Board ;

// creates a new board
Board Board_New(void);

// checks if current shape position intersects with any
// board's blocks
bool Board_Intersect
(
	const Board board,   // board to intersect against
	const Shape *shape   // shape to intersect with
);

// adds shape to board
void Board_SetShape
(
	Board board,        // board to add shape to
	const Shape *shape  // shape added
);

// removes shaoe from board
void Board_RemoveShape
(
	Board board,        // board from which shape is removed
	const Shape *shape  // shape to remove
);

// clears rows where all columns are set
// returns the number of rows cleared
int Board_ClearFullRows
(
	Board board         // board to clear rows from
);

// prints board to stdout
void Board_Print
(
	const Board board   // board to print
);

// free board
void Board_Free
(
	Board *board
);

#endif

