#include "../shape.h"

// S shape
//
//  OO
// O0

Shape *S_New(void)
{
	Shape *S = NEW_SHAPE(4) ;
	assert (S != NULL) ;

	S->name      =  "S"           ;
	S->type      =  SHAPE_TYPE_S  ;

	S->blocks[0] = (Point) {BOARD_WIDTH / 2 - 1, BOARD_HEIGHT - 1} ;
	S->blocks[1] = (Point) {BOARD_WIDTH / 2 - 2, BOARD_HEIGHT - 1} ;
	S->blocks[2] = (Point) {BOARD_WIDTH / 2 - 1, BOARD_HEIGHT    } ;
	S->blocks[3] = (Point) {BOARD_WIDTH / 2,     BOARD_HEIGHT    } ;

	return S ;
}

