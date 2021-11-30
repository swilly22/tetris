#include "shape.h"
#include "tetris.h"
#include <math.h>
#include <stdlib.h>

static void Shape_Shift
(
	Shape *shape,  // shape to shift
	int units
) {
	for (uint i = 0 ; i < shape->n_blocks ; i++)
	{
		shape->blocks[i].x += units ;
	}
}

static void Shape_Push
(
	Shape *shape,
	int units
) {
	
	for (uint i = 0 ; i < shape->n_blocks ; i++)
	{
		shape->blocks[i].y += units ;
	}
}

void Shape_Rotate
(
	Shape *shape,
	Rotation_Dir dir
) {
	// validate input

	ASSERT_NOT_NULL (shape) ;
	ASSERT (dir == CLOCKWISE || dir == COUNTER_CLOCKWISE) ;

	if (shape->type == SHAPE_TYPE_O)
	{
		// the O shape doesn't rotates
		return;
	}

	// block 0 is the shape pivot around which the shape rotates
	Point pivot = shape->blocks[0] ;

	for (uint i = 1 ; i < shape->n_blocks ; i++)
	{
		Point *block = shape->blocks + i ;

		// translate point around origin (0,0)
		double new_x ;
		double new_y ;
		int x = block->x - pivot.x ;
		int y = block->y - pivot.y ;

		// rotate point by PI/2
		if (dir == CLOCKWISE)
		{
			// rotate clockwise
			new_x = (cos (M_PI/2) * x) + (sin (M_PI/2) * y) ;
			new_y = (cos (M_PI/2) * y) - (sin (M_PI/2) * x) ;
		}
		else 
		{
			// rotate counter clockwise
			new_x = (cos (M_PI/2) * x) - (sin (M_PI/2) * y) ;
			new_y = (sin (M_PI/2) * x) + (cos (M_PI/2) * y) ;
		}

		block->x += new_x - x ;
		block->y += new_y - y ;
	}
}

// shift shape right by one unit
void Shape_ShiftRight
(
	Shape *shape  // shape to shift
) {
	Shape_Shift (shape, 1) ;
}

// shift shape right by one unit
void Shape_ShiftLeft
(
	Shape *shape  // shape to shift
) {

	Shape_Shift (shape, -1) ;
}

// pushes shape one row up
void Shape_PushUp
(
	Shape *shape  // shape to push upwards
) {
	ASSERT_NOT_NULL (shape) ;

	Shape_Push (shape, 1) ;
}

// pushes shape one row down 
void Shape_PushDown
(
	Shape *shape  // shape to push downwards
) {
	ASSERT_NOT_NULL (shape) ;

	Shape_Push (shape, -1) ;
}

void Shape_Print
(
	const Shape *shape
) {
	ASSERT_NOT_NULL (shape) ;

	printf ("%s\n", shape->name) ;
	
	for (uint i = 0 ; i < shape->n_blocks ; i++)
	{
		printf ("(%d,%d)\n", shape->blocks[i].x, shape->blocks[i].y) ;
	}
}

Shape *Shape_RandomShape (void)
{
	Shape *shape = NULL ;
	int type = rand() % 5 ;

	// TODO: use an array of constructors
	// Shape *shape = constructors[type] () ;

	switch (type)
	{
		case SHAPE_TYPE_I :
			shape = I_New () ;
			break ;
		case SHAPE_TYPE_L :
			shape = L_New () ;
			break ;
		case SHAPE_TYPE_O :
			shape = O_New () ;
			break ;
		case SHAPE_TYPE_S :
			shape = S_New () ;
			break ;
		case SHAPE_TYPE_T :
			shape = T_New () ;
			break ;
		default :
			assert (false) ;
			break ;
	}

	assert (shape != NULL) ;
	return shape ;
}

void Shape_Free
(
	Shape **shape
) {

	if (*shape == NULL) return ;

	free (*shape) ;
	*shape = NULL ;
}

