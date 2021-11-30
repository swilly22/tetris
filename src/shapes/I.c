#include "../shape.h"

// I shape
//
// O0OO

Shape *I_New(void)
{
	Shape *I = NEW_SHAPE(4) ;
	ASSERT_NOT_NULL (I) ;

	I->name      =  "I"           ;
	I->type      =  SHAPE_TYPE_I  ;

	I->blocks[0] = (Point) {BOARD_WIDTH / 2 - 1, BOARD_HEIGHT - 1} ;
	I->blocks[1] = (Point) {BOARD_WIDTH / 2 - 2, BOARD_HEIGHT - 1} ;
	I->blocks[2] = (Point) {BOARD_WIDTH / 2,     BOARD_HEIGHT - 1} ;
	I->blocks[3] = (Point) {BOARD_WIDTH / 2 + 1, BOARD_HEIGHT - 1} ;

	return I ;
}

