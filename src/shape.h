#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "tetris.h"
#include <stdlib.h>
#include <sys/types.h>

#define NEW_SHAPE(blocks) ({                                                  \
	Shape *s = calloc(sizeof (Shape) + ((blocks) * sizeof (Point)), 1) ;  \
	s->n_blocks = blocks ;                                                \
	s ;                                                                   \
})

// shape rotation direction
typedef enum
{
	CLOCKWISE,
	COUNTER_CLOCKWISE
} Rotation_Dir ;

typedef enum
{
	SHAPE_TYPE_I,  // straight tetracube
	SHAPE_TYPE_L,  // L-tetracube
	SHAPE_TYPE_O,  // square tetracube
	SHAPE_TYPE_S,  // skew tetracube
	SHAPE_TYPE_T   // T-tetracube
} Shape_Type ;

// x,y point
typedef struct
{
	int x;  // point x position
	int y;  // point y position
} Point ;

typedef struct
{
	Shape_Type type;      // shape type
	const char *name;     // shape name
	uint n_blocks;        // number of blocks in shape
	Point blocks[];       // shape's blocks
} Shape ;

// rotate shape either clockwise or counter-clockwise
void Shape_Rotate
(
	Shape *shape,     // shape to rotate
	Rotation_Dir dir  // rotation direction
) ;

// shift shape right by one unit
void Shape_ShiftRight
(
	Shape *shape  // shape to shift
) ;

// shift shape left by one unit
void Shape_ShiftLeft
(
	Shape *shape  // shape to shift
) ;

// pushes shape one row down 
void Shape_PushUp
(
	Shape *shape  // shape to push upwards
) ;

// pushes shape one row down 
void Shape_PushDown
(
	Shape *shape  // shape to push downwards
) ;

// print shape
void Shape_Print
(
	const Shape *shape
) ;

//------------------------------------------------------------------------------
// shapes
//------------------------------------------------------------------------------

Shape *I_New (void) ;
Shape *L_New (void) ;
Shape *O_New (void) ;
Shape *S_New (void) ;
Shape *T_New (void) ;

// get a random shape
Shape *Shape_RandomShape (void) ;

// free shape
void Shape_Free (Shape **shape) ;

#endif

