#include "../shape.h"

// L shape
//
// O
// 0OO

Shape *L_New(void)
{
	Shape *L = NEW_SHAPE(4) ;
	assert (L != NULL) ;

	L->name      =  "L"           ;
	L->type      =  SHAPE_TYPE_L  ;

	L->blocks[0] = (Point) {BOARD_WIDTH / 2 - 2, BOARD_HEIGHT - 1} ;
	L->blocks[1] = (Point) {BOARD_WIDTH / 2 - 1, BOARD_HEIGHT - 1} ;
	L->blocks[2] = (Point) {BOARD_WIDTH / 2,     BOARD_HEIGHT - 1} ;
	L->blocks[3] = (Point) {BOARD_WIDTH / 2 - 2, BOARD_HEIGHT    } ;

	return L ;
}

