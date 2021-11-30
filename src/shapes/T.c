#include "../shape.h"

// T shape
//
//  O
// O0O

Shape *T_New(void)
{
	Shape *T = NEW_SHAPE(4) ;
	assert(T != NULL) ;

	T->name      =  "T"           ;
	T->type      =  SHAPE_TYPE_T  ;

	T->blocks[0] = (Point) {BOARD_WIDTH / 2 - 1, BOARD_HEIGHT - 1} ;
	T->blocks[1] = (Point) {BOARD_WIDTH / 2 - 2, BOARD_HEIGHT - 1} ;
	T->blocks[2] = (Point) {BOARD_WIDTH / 2,     BOARD_HEIGHT - 1} ;
	T->blocks[3] = (Point) {BOARD_WIDTH / 2 - 1, BOARD_HEIGHT    } ;

	return T ;
}

