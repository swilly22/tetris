#include "../shape.h"

// Square shape
//
// OO
// 0O

Shape *O_New(void)
{
	Shape *O = NEW_SHAPE(4) ;
	assert(O != NULL) ;

	O->name      =  "O"           ;
	O->type      =  SHAPE_TYPE_O  ;

	O->blocks[0] = (Point) {BOARD_WIDTH / 2 - 1, BOARD_HEIGHT - 1} ;
	O->blocks[1] = (Point) {BOARD_WIDTH / 2,     BOARD_HEIGHT - 1} ;
	O->blocks[2] = (Point) {BOARD_WIDTH / 2 - 1, BOARD_HEIGHT    } ;
	O->blocks[3] = (Point) {BOARD_WIDTH / 2,     BOARD_HEIGHT    } ;

	return O ;
}

