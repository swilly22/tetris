#include <tetris_test.h>
#include "../shape.h"

//******************************************************************************

void setup (void)
{
	// seed random
	time_t t ;
	srand ((unsigned) time (&t)) ;
}

void test_Shape_I_New (void)
{
	setup () ;

	//------------------------------------------------------------------------
	// validate the I shape
	//------------------------------------------------------------------------

	Shape *I = I_New () ;

	TEST_CHECK (I != NULL) ;
	TEST_CHECK (strcmp (I->name, "I") == 0) ;
	TEST_CHECK (I->type == SHAPE_TYPE_I) ;
	TEST_CHECK (I->n_blocks == 4) ;

	TEST_CHECK (I->blocks[0].x == BOARD_WIDTH / 2 - 1) ;
	TEST_CHECK (I->blocks[0].y == BOARD_HEIGHT - 1) ;

	TEST_CHECK (I->blocks[1].x == BOARD_WIDTH / 2 - 2) ;
	TEST_CHECK (I->blocks[1].y == BOARD_HEIGHT - 1) ;

	TEST_CHECK (I->blocks[2].x == BOARD_WIDTH / 2) ;
	TEST_CHECK (I->blocks[2].y == BOARD_HEIGHT - 1) ;

	TEST_CHECK (I->blocks[3].x == BOARD_WIDTH / 2 + 1) ;
	TEST_CHECK (I->blocks[3].y == BOARD_HEIGHT - 1) ;

	Shape_Free (&I) ;
}

void test_Shape_L_New (void)
{
	setup () ;

	//------------------------------------------------------------------------
	// validate the L shape
	//------------------------------------------------------------------------

	Shape *L = L_New () ;

	TEST_CHECK (L != NULL) ;
	TEST_CHECK (strcmp (L->name, "L") == 0) ;
	TEST_CHECK (L->type == SHAPE_TYPE_L) ;
	TEST_CHECK (L->n_blocks == 4) ;

	TEST_CHECK (L->blocks[0].x == BOARD_WIDTH / 2 - 2) ;
	TEST_CHECK (L->blocks[0].y == BOARD_HEIGHT - 1) ;

	TEST_CHECK (L->blocks[1].x == BOARD_WIDTH / 2 - 1) ;
	TEST_CHECK (L->blocks[1].y == BOARD_HEIGHT - 1) ;

	TEST_CHECK (L->blocks[2].x == BOARD_WIDTH / 2) ;
	TEST_CHECK (L->blocks[2].y == BOARD_HEIGHT - 1) ;

	TEST_CHECK (L->blocks[3].x == BOARD_WIDTH / 2 - 2) ;
	TEST_CHECK (L->blocks[3].y == BOARD_HEIGHT) ;

	Shape_Free (&L) ;
}

void test_Shape_O_New (void)
{
	setup () ;

	//------------------------------------------------------------------------
	// validate the O shape
	//------------------------------------------------------------------------

	Shape *O = O_New () ;

	TEST_CHECK (O != NULL) ;
	TEST_CHECK (strcmp (O->name, "O") == 0) ;
	TEST_CHECK (O->type == SHAPE_TYPE_O) ;
	TEST_CHECK (O->n_blocks == 4) ;

	TEST_CHECK (O->blocks[0].x == BOARD_WIDTH / 2 - 1) ;
	TEST_CHECK (O->blocks[0].y == BOARD_HEIGHT - 1) ;

	TEST_CHECK (O->blocks[1].x == BOARD_WIDTH / 2) ;
	TEST_CHECK (O->blocks[1].y == BOARD_HEIGHT - 1) ;

	TEST_CHECK (O->blocks[2].x == BOARD_WIDTH / 2 - 1) ;
	TEST_CHECK (O->blocks[2].y == BOARD_HEIGHT) ;

	TEST_CHECK (O->blocks[3].x == BOARD_WIDTH / 2) ;
	TEST_CHECK (O->blocks[3].y == BOARD_HEIGHT) ;

	Shape_Free (&O) ;
}

void test_Shape_S_New (void)
{
	setup () ;

	//------------------------------------------------------------------------
	// validate the S shape
	//------------------------------------------------------------------------

	Shape *S = S_New () ;

	TEST_CHECK (S != NULL) ;
	TEST_CHECK (strcmp (S->name, "S") == 0) ;
	TEST_CHECK (S->type == SHAPE_TYPE_S) ;
	TEST_CHECK (S->n_blocks == 4) ;

	TEST_CHECK (S->blocks[0].x == BOARD_WIDTH / 2 - 1) ;
	TEST_CHECK (S->blocks[0].y == BOARD_HEIGHT - 1) ;

	TEST_CHECK (S->blocks[1].x == BOARD_WIDTH / 2 - 2) ;
	TEST_CHECK (S->blocks[1].y == BOARD_HEIGHT - 1) ;

	TEST_CHECK (S->blocks[2].x == BOARD_WIDTH / 2 - 1) ;
	TEST_CHECK (S->blocks[2].y == BOARD_HEIGHT) ;

	TEST_CHECK (S->blocks[3].x == BOARD_WIDTH / 2) ;
	TEST_CHECK (S->blocks[3].y == BOARD_HEIGHT) ;

	Shape_Free (&S) ;
}

void test_Shape_T_New (void)
{
	setup () ;

	//------------------------------------------------------------------------
	// validate the T shape
	//------------------------------------------------------------------------

	Shape *T = T_New () ;

	TEST_CHECK (T != NULL) ;
	TEST_CHECK (strcmp (T->name, "T") == 0) ;
	TEST_CHECK (T->type == SHAPE_TYPE_T) ;
	TEST_CHECK (T->n_blocks == 4) ;

	TEST_CHECK (T->blocks[0].x == BOARD_WIDTH / 2 - 1) ;
	TEST_CHECK (T->blocks[0].y == BOARD_HEIGHT - 1) ;

	TEST_CHECK (T->blocks[1].x == BOARD_WIDTH / 2 - 2) ;
	TEST_CHECK (T->blocks[1].y == BOARD_HEIGHT - 1) ;

	TEST_CHECK (T->blocks[2].x == BOARD_WIDTH / 2) ;
	TEST_CHECK (T->blocks[2].y == BOARD_HEIGHT - 1) ;

	TEST_CHECK (T->blocks[3].x == BOARD_WIDTH / 2 - 1) ;
	TEST_CHECK (T->blocks[3].y == BOARD_HEIGHT) ;

	Shape_Free (&T) ;
}

//******************************************************************************

void test_Shape_Shift (void)
{
	setup () ;

	Shape *s = Shape_RandomShape () ;
	Point blocks[s->n_blocks] ;
	memcpy (blocks, s->blocks, sizeof(Point) * s->n_blocks) ;

	// shift right, offset by +1
	Shape_ShiftRight (s) ;
	for (int i = 0 ; i < s->n_blocks ; i++)
	{
		TEST_CHECK (blocks[i].x + 1 == s->blocks[i].x) ;
		TEST_CHECK (blocks[i].y == s->blocks[i].y) ;
	}

	// shift left, restore to original position
	Shape_ShiftLeft (s) ;
	for (int i = 0 ; i < s->n_blocks ; i++)
	{
		TEST_CHECK (blocks[i].x == s->blocks[i].x) ;
		TEST_CHECK (blocks[i].y == s->blocks[i].y) ;
	}

	// shift left again, offset by -1
	Shape_ShiftLeft (s) ;
	for (int i = 0 ; i < s->n_blocks ; i++)
	{
		TEST_CHECK (blocks[i].x - 1 == s->blocks[i].x) ;
		TEST_CHECK (blocks[i].y == s->blocks[i].y) ;
	}

	Shape_Free (&s) ;
}

//******************************************************************************

void test_Shape_Push (void)
{
	setup () ;

	Shape *s = Shape_RandomShape () ;
	Point blocks[s->n_blocks] ;
	memcpy (blocks, s->blocks, sizeof(Point) * s->n_blocks) ;

	// push upwards, offset by 1
	Shape_PushUp (s) ;
	for (int i = 0 ; i < s->n_blocks ; i++)
	{
		TEST_CHECK (blocks[i].y + 1 == s->blocks[i].y) ;
		TEST_CHECK (blocks[i].x == s->blocks[i].x) ;
	}

	// push downward, restore to original position
	Shape_PushDown (s) ;
	for (int i = 0 ; i < s->n_blocks ; i++)
	{
		TEST_CHECK (blocks[i].y == s->blocks[i].y) ;
		TEST_CHECK (blocks[i].x == s->blocks[i].x) ;
	}

	// push downward again, offset by -1
	Shape_PushDown (s) ;
	for (int i = 0 ; i < s->n_blocks ; i++)
	{
		TEST_CHECK (blocks[i].y - 1 == s->blocks[i].y) ;
		TEST_CHECK (blocks[i].x == s->blocks[i].x) ;
	}

	Shape_Free (&s) ;
}

//******************************************************************************

void test_Shape_I_Rotate (void)
{
	setup () ;

	Shape *I = I_New () ;

	// backup shape original position
	Point blocks[I->n_blocks] ;
	memcpy (blocks, I->blocks, sizeof(Point) * I->n_blocks) ;

	// rotate shape 4 times to complete a full cycle
	// returning to the original position

	// rotate shape by PI/2 counter clockwise
	// O0OO
	//
	// O
	// O
	// 0
	// O

	Shape_Rotate (I, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (I->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[1].y == blocks[0].y - 1) ;

	TEST_CHECK (I->blocks[2].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[2].y == blocks[0].y + 1) ;

	TEST_CHECK (I->blocks[3].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[3].y == blocks[0].y + 2) ;

	memcpy (blocks, I->blocks, sizeof(Point) * I->n_blocks) ;

	// rotate shape by PI/2 counter clockwise
	//
	// O
	// O
	// 0
	// O
	//
	// OO0O

	Shape_Rotate (I, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (I->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[1].x == blocks[0].x + 1) ;
	TEST_CHECK (I->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[2].x == blocks[0].x - 1) ;
	TEST_CHECK (I->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[3].x == blocks[0].x - 2) ;
	TEST_CHECK (I->blocks[3].y == blocks[0].y) ;

	memcpy (blocks, I->blocks, sizeof(Point) * I->n_blocks) ;

	// rotate shape by PI/2 counter clockwise
	//
	// OO0O
	//
	// O
	// 0
	// O
	// O

	Shape_Rotate (I, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (I->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[1].y == blocks[0].y + 1) ;

	TEST_CHECK (I->blocks[2].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[2].y == blocks[0].y - 1) ;

	TEST_CHECK (I->blocks[3].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[3].y == blocks[0].y - 2) ;

	memcpy (blocks, I->blocks, sizeof(Point) * I->n_blocks) ;

	// rotate shape by PI/2 counter clockwise
	//
	// O
	// 0
	// O
	// O
	//
	// O0OO

	Shape_Rotate (I, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (I->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[1].x == blocks[0].x - 1) ;
	TEST_CHECK (I->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[2].x == blocks[0].x + 1) ;
	TEST_CHECK (I->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[3].x == blocks[0].x + 2) ;
	TEST_CHECK (I->blocks[3].y == blocks[0].y) ;

	memcpy (blocks, I->blocks, sizeof(Point) * I->n_blocks) ;

	//--------------------------------------------------------------------------

	// rotate shape 4 times to complete a full cycle
	// returning to the original position

	// rotate shape by PI/2 clockwise
	// O0OO
	//
	// O
	// 0
	// O
	// O

	Shape_Rotate (I, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (I->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[1].y == blocks[0].y + 1) ;

	TEST_CHECK (I->blocks[2].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[2].y == blocks[0].y - 1) ;

	TEST_CHECK (I->blocks[3].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[3].y == blocks[0].y - 2) ;

	memcpy (blocks, I->blocks, sizeof(Point) * I->n_blocks) ;

	// rotate shape by PI/2 clockwise
	//
	// O
	// 0
	// O
	// O
	//
	// OO0O

	Shape_Rotate (I, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (I->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[1].x == blocks[0].x + 1) ;
	TEST_CHECK (I->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[2].x == blocks[0].x - 1) ;
	TEST_CHECK (I->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[3].x == blocks[0].x - 2) ;
	TEST_CHECK (I->blocks[3].y == blocks[0].y) ;

	memcpy (blocks, I->blocks, sizeof(Point) * I->n_blocks) ;

	// rotate shape by PI/2 clockwise
	//
	// OO0O
	//
	// O
	// O
	// 0
	// O

	Shape_Rotate (I, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (I->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[1].y == blocks[0].y - 1) ;

	TEST_CHECK (I->blocks[2].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[2].y == blocks[0].y + 1) ;

	TEST_CHECK (I->blocks[3].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[3].y == blocks[0].y + 2) ;

	memcpy (blocks, I->blocks, sizeof(Point) * I->n_blocks) ;

	// rotate shape by PI/2 clockwise
	//
	// O
	// O
	// 0
	// O
	//
	// O0OO

	Shape_Rotate (I, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (I->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (I->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[1].x == blocks[0].x - 1) ;
	TEST_CHECK (I->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[2].x == blocks[0].x + 1) ;
	TEST_CHECK (I->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (I->blocks[3].x == blocks[0].x + 2) ;
	TEST_CHECK (I->blocks[3].y == blocks[0].y) ;

	Shape_Free (&I) ;
}

//******************************************************************************

void test_Shape_L_Rotate (void)
{
	setup () ;

	Shape *L = L_New () ;

	// backup shape original position
	Point blocks[L->n_blocks] ;
	memcpy (blocks, L->blocks, sizeof(Point) * L->n_blocks) ;

	// rotate shape 4 times to complete a full cycle
	// returning to the original position

	// rotate shape by PI/2 counter clockwise
	// O
	// 0OO
	//
	//  O
	//  O
	// O0

	Shape_Rotate (L, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (L->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[1].y == blocks[0].y + 1) ;

	TEST_CHECK (L->blocks[2].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[2].y == blocks[0].y + 2) ;

	TEST_CHECK (L->blocks[3].x == blocks[0].x - 1) ;
	TEST_CHECK (L->blocks[3].y == blocks[0].y) ;

	memcpy (blocks, L->blocks, sizeof(Point) * L->n_blocks) ;

	// rotate shape by PI/2 counter clockwise
	//
	//  O
	//  O
	// O0
	//
	// OO0
	//   O

	Shape_Rotate (L, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (L->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[1].x == blocks[0].x - 1) ;
	TEST_CHECK (L->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[2].x == blocks[0].x - 2) ;
	TEST_CHECK (L->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[3].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[3].y == blocks[0].y - 1) ;

	memcpy (blocks, L->blocks, sizeof(Point) * L->n_blocks) ;

	// rotate shape by PI/2 counter clockwise
	//
	// OO0
	//   O
	//
	// 0O
	// O
	// O

	Shape_Rotate (L, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (L->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[1].y == blocks[0].y - 1) ;

	TEST_CHECK (L->blocks[2].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[2].y == blocks[0].y - 2) ;

	TEST_CHECK (L->blocks[3].x == blocks[0].x + 1) ;
	TEST_CHECK (L->blocks[3].y == blocks[0].y) ;

	memcpy (blocks, L->blocks, sizeof(Point) * L->n_blocks) ;

	// rotate shape by PI/2 counter clockwise
	//
	// 0O
	// O
	// O
	//
	// O
	// 0OO

	Shape_Rotate (L, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (L->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[1].x == blocks[0].x + 1) ;
	TEST_CHECK (L->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[2].x == blocks[0].x + 2) ;
	TEST_CHECK (L->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[3].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[3].y == blocks[0].y + 1) ;

	memcpy (blocks, L->blocks, sizeof(Point) * L->n_blocks) ;

	//--------------------------------------------------------------------------

	// rotate shape 4 times to complete a full cycle
	// returning to the original position

	// rotate shape by PI/2 clockwise
	// O
	// 0OO
	//
	// 0O
	// O
	// O

	Shape_Rotate (L, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (L->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[1].y == blocks[0].y - 1) ;

	TEST_CHECK (L->blocks[2].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[2].y == blocks[0].y - 2) ;

	TEST_CHECK (L->blocks[3].x == blocks[0].x + 1) ;
	TEST_CHECK (L->blocks[3].y == blocks[0].y) ;

	memcpy (blocks, L->blocks, sizeof(Point) * L->n_blocks) ;

	// rotate shape by PI/2 clockwise
	//
	// 0O
	// O
	// O
	//
	// OO0
	//   O

	Shape_Rotate (L, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (L->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[1].x == blocks[0].x - 1) ;
	TEST_CHECK (L->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[2].x == blocks[0].x - 2) ;
	TEST_CHECK (L->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[3].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[3].y == blocks[0].y - 1) ;

	memcpy (blocks, L->blocks, sizeof(Point) * L->n_blocks) ;

	// rotate shape by PI/2 clockwise
	//
	// OO0
	//   O
	//
	//  O
	//  O
	// O0

	Shape_Rotate (L, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (L->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[1].y == blocks[0].y + 1) ;

	TEST_CHECK (L->blocks[2].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[2].y == blocks[0].y + 2) ;

	TEST_CHECK (L->blocks[3].x == blocks[0].x - 1) ;
	TEST_CHECK (L->blocks[3].y == blocks[0].y) ;

	memcpy (blocks, L->blocks, sizeof(Point) * L->n_blocks) ;

	// rotate shape by PI/2 clockwise
	//
	//  O
	//  O
	// O0
	//
	// O
	// 0OO

	Shape_Rotate (L, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (L->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[1].x == blocks[0].x + 1) ;
	TEST_CHECK (L->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[2].x == blocks[0].x + 2) ;
	TEST_CHECK (L->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (L->blocks[3].x == blocks[0].x) ;
	TEST_CHECK (L->blocks[3].y == blocks[0].y + 1) ;

	Shape_Free (&L) ;
}

//******************************************************************************

void test_Shape_O_Rotate (void)
{
	setup () ;

	Shape *O = O_New () ;

	// backup shape original position
	Point blocks[O->n_blocks] ;
	memcpy (blocks, O->blocks, sizeof(Point) * O->n_blocks) ;

	// rotate shape 4 times to complete a full cycle
	// returning to the original position

	for (int i = 0 ; i < 4 ; i++)
	{
		// rotate shape by PI/2 counter clockwise
		// OO
		// 0O
		//
		// OO
		// 0O

		Shape_Rotate (O, COUNTER_CLOCKWISE) ;

		// pivot should not move
		TEST_CHECK (O->blocks[0].x == blocks[0].x) ;
		TEST_CHECK (O->blocks[0].y == blocks[0].y) ;

		TEST_CHECK (O->blocks[1].x == blocks[0].x + 1) ;
		TEST_CHECK (O->blocks[1].y == blocks[0].y) ;

		TEST_CHECK (O->blocks[2].x == blocks[0].x) ;
		TEST_CHECK (O->blocks[2].y == blocks[0].y + 1) ;

		TEST_CHECK (O->blocks[3].x == blocks[0].x + 1) ;
		TEST_CHECK (O->blocks[3].y == blocks[0].y + 1) ;

		memcpy (blocks, O->blocks, sizeof(Point) * O->n_blocks) ;
	}

	//--------------------------------------------------------------------------

	// rotate shape 4 times to complete a full cycle
	// returning to the original position

	for (int i = 0 ; i < 4 ; i++)
	{
		// rotate shape by PI/2 clockwise
		// OO
		// 0O
		//
		// OO
		// 0O

		Shape_Rotate (O, CLOCKWISE) ;

		// pivot should not move
		TEST_CHECK (O->blocks[0].x == blocks[0].x) ;
		TEST_CHECK (O->blocks[0].y == blocks[0].y) ;

		TEST_CHECK (O->blocks[1].x == blocks[0].x + 1) ;
		TEST_CHECK (O->blocks[1].y == blocks[0].y) ;

		TEST_CHECK (O->blocks[2].x == blocks[0].x) ;
		TEST_CHECK (O->blocks[2].y == blocks[0].y + 1) ;

		TEST_CHECK (O->blocks[3].x == blocks[0].x + 1) ;
		TEST_CHECK (O->blocks[3].y == blocks[0].y + 1) ;

		memcpy (blocks, O->blocks, sizeof(Point) * O->n_blocks) ;
	}

	Shape_Free (&O) ;
}

//******************************************************************************

void test_Shape_S_Rotate (void)
{
	setup () ;

	Shape *S = S_New () ;

	// backup shape original position
	Point blocks[S->n_blocks] ;
	memcpy (blocks, S->blocks, sizeof(Point) * S->n_blocks) ;

	// rotate shape 4 times to complete a full cycle
	// returning to the original position

	// rotate shape by PI/2 counter clockwise
	//  OO
	// O0
	//
	// O
	// O0
	//  O

	printf ("S->blocks[3].x = %d\n", S->blocks[3].x) ;
	printf ("S->blocks[3].y = %d\n", S->blocks[3].y) ;
	Shape_Rotate (S, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (S->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[1].y == blocks[0].y - 1) ;

	TEST_CHECK (S->blocks[2].x == blocks[0].x - 1) ;
	TEST_CHECK (S->blocks[2].y == blocks[0].y) ;

	printf ("S->blocks[3].x = %d\n", S->blocks[3].x) ;
	printf ("blocks[0].x - 1 = %d\n", blocks[0].x - 1) ;
	printf ("S->blocks[3].y = %d\n", S->blocks[3].y) ;
	printf ("blocks[0].y + 1 = %d\n", blocks[0].y + 1) ;
	TEST_CHECK (S->blocks[3].x == blocks[0].x - 1) ;
	TEST_CHECK (S->blocks[3].y == blocks[0].y + 1) ;

	return;
	memcpy (blocks, S->blocks, sizeof(Point) * S->n_blocks) ;

	// rotate shape by PI/2 counter clockwise
	//
	// O
	// O0
	//  O
	//
	//  0O
	// OO

	Shape_Rotate (S, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (S->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[1].x == blocks[0].x + 1) ;
	TEST_CHECK (S->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[2].x == blocks[0].x - 1) ;
	TEST_CHECK (S->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[3].x == blocks[0].x - 1) ;
	TEST_CHECK (S->blocks[3].y == blocks[0].y - 1) ;

	memcpy (blocks, S->blocks, sizeof(Point) * S->n_blocks) ;

	// rotate shape by PI/2 counter clockwise
	//
	//  0O
	// OO
	//
	// O
	// 0O
	//  O

	Shape_Rotate (S, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (S->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[1].y == blocks[0].y + 1) ;

	TEST_CHECK (S->blocks[2].x == blocks[0].x + 1) ;
	TEST_CHECK (S->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[3].x == blocks[0].x + 1) ;
	TEST_CHECK (S->blocks[3].y == blocks[0].y - 1) ;

	memcpy (blocks, S->blocks, sizeof(Point) * S->n_blocks) ;

	// rotate shape by PI/2 counter clockwise
	//
	// O
	// 0O
	//  O
	//
	//  OO
	// O0

	Shape_Rotate (S, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (S->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[1].x == blocks[0].x - 1) ;
	TEST_CHECK (S->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[2].x == blocks[0].x + 1) ;
	TEST_CHECK (S->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[3].x == blocks[0].x + 2) ;
	TEST_CHECK (S->blocks[3].y == blocks[0].y) ;

	memcpy (blocks, S->blocks, sizeof(Point) * S->n_blocks) ;

	//--------------------------------------------------------------------------

	// rotate shape 4 times to complete a full cycle
	// returning to the original position

	// rotate shape by PI/2 clockwise
	//  OO
	// O0
	//
	// O
	// 0O
	//  O

	Shape_Rotate (S, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (S->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[1].y == blocks[0].y + 1) ;

	TEST_CHECK (S->blocks[2].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[2].y == blocks[0].y - 1) ;

	TEST_CHECK (S->blocks[3].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[3].y == blocks[0].y - 2) ;

	memcpy (blocks, S->blocks, sizeof(Point) * S->n_blocks) ;

	// rotate shape by PI/2 clockwise
	//
	// O
	// 0O
	//  O
	//
	//  0O
	// OO

	Shape_Rotate (S, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (S->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[1].x == blocks[0].x + 1) ;
	TEST_CHECK (S->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[2].x == blocks[0].x - 1) ;
	TEST_CHECK (S->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[3].x == blocks[0].x - 2) ;
	TEST_CHECK (S->blocks[3].y == blocks[0].y) ;

	memcpy (blocks, S->blocks, sizeof(Point) * S->n_blocks) ;

	// rotate shape by PI/2 clockwise
	//
	//  0O
	// OO
	//
	// O
	// O0
	//  O

	Shape_Rotate (S, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (S->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[1].y == blocks[0].y - 1) ;

	TEST_CHECK (S->blocks[2].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[2].y == blocks[0].y + 1) ;

	TEST_CHECK (S->blocks[3].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[3].y == blocks[0].y + 2) ;

	memcpy (blocks, S->blocks, sizeof(Point) * S->n_blocks) ;

	// rotate shape by PI/2 clockwise
	//
	// O
	// O0
	//  O
	//
	//  OO
	// O0

	Shape_Rotate (S, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (S->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (S->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[1].x == blocks[0].x - 1) ;
	TEST_CHECK (S->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[2].x == blocks[0].x + 1) ;
	TEST_CHECK (S->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (S->blocks[3].x == blocks[0].x + 2) ;
	TEST_CHECK (S->blocks[3].y == blocks[0].y) ;

	Shape_Free (&S) ;
}

//******************************************************************************

void test_Shape_T_Rotate (void)
{
	setup () ;

	Shape *T = T_New () ;

	// backup shape original position
	Point blocks[T->n_blocks] ;
	memcpy (blocks, T->blocks, sizeof(Point) * T->n_blocks) ;

	// rotate shape 4 times to complete a full cycle
	// returning to the original position

	// rotate shape by PI/2 counter clockwise
	//  O
	// O0O
	//
	//  O
	// O0
	//  O

	Shape_Rotate (T, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (T->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[1].y == blocks[0].y - 1) ;

	TEST_CHECK (T->blocks[2].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[2].y == blocks[0].y + 1) ;

	TEST_CHECK (T->blocks[3].x == blocks[0].x - 1) ;
	TEST_CHECK (T->blocks[3].y == blocks[0].y) ;

	memcpy (blocks, T->blocks, sizeof(Point) * T->n_blocks) ;

	// rotate shape by PI/2 counter clockwise
	//
	//  O
	// O0
	//  O
	//
	// O0O
	//  O

	Shape_Rotate (T, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (T->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[1].x == blocks[0].x + 1) ;
	TEST_CHECK (T->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[2].x == blocks[0].x - 1) ;
	TEST_CHECK (T->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[3].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[3].y == blocks[0].y - 1) ;

	memcpy (blocks, T->blocks, sizeof(Point) * T->n_blocks) ;

	// rotate shape by PI/2 counter clockwise
	//
	// O0O
	//  O
	//
	// O
	// 0O
	// O

	Shape_Rotate (T, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (T->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[1].y == blocks[0].y + 1) ;

	TEST_CHECK (T->blocks[2].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[2].y == blocks[0].y - 1) ;

	TEST_CHECK (T->blocks[3].x == blocks[0].x + 1) ;
	TEST_CHECK (T->blocks[3].y == blocks[0].y) ;

	memcpy (blocks, T->blocks, sizeof(Point) * T->n_blocks) ;

	// rotate shape by PI/2 counter clockwise
	//
	// O
	// 0O
	// O
	//
	//  O
	// O0O

	Shape_Rotate (T, COUNTER_CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (T->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[1].x == blocks[0].x - 1) ;
	TEST_CHECK (T->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[2].x == blocks[0].x + 1) ;
	TEST_CHECK (T->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[3].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[3].y == blocks[0].y + 1) ;

	memcpy (blocks, T->blocks, sizeof(Point) * T->n_blocks) ;

	//--------------------------------------------------------------------------

	// rotate shape 4 times to complete a full cycle
	// returning to the original position

	// rotate shape by PI/2 clockwise
	//  O
	// O0O
	//
	// O
	// 0O
	// O

	Shape_Rotate (T, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (T->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[1].y == blocks[1].y + 1) ;

	TEST_CHECK (T->blocks[2].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[2].y == blocks[2].y - 1) ;

	TEST_CHECK (T->blocks[3].x == blocks[0].x + 1) ;
	TEST_CHECK (T->blocks[3].y == blocks[0].y) ;

	memcpy (blocks, T->blocks, sizeof(Point) * T->n_blocks) ;

	// rotate shape by PI/2 clockwise
	//
	// O
	// 0O
	// O
	//
	// O0O
	//  O

	Shape_Rotate (T, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (T->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[1].x == blocks[0].x + 1) ;
	TEST_CHECK (T->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[2].x == blocks[0].x - 1) ;
	TEST_CHECK (T->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[3].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[3].y == blocks[0].y - 1) ;

	memcpy (blocks, T->blocks, sizeof(Point) * T->n_blocks) ;

	// rotate shape by PI/2 clockwise
	//
	// O0O
	//  O
	//
	//  O
	// O0
	//  O

	Shape_Rotate (T, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (T->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[1].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[1].y == blocks[0].y - 1) ;

	TEST_CHECK (T->blocks[2].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[2].y == blocks[0].y + 1) ;

	TEST_CHECK (T->blocks[3].x == blocks[0].x - 1) ;
	TEST_CHECK (T->blocks[3].y == blocks[0].y) ;

	memcpy (blocks, T->blocks, sizeof(Point) * T->n_blocks) ;

	// rotate shape by PI/2 clockwise
	//
	//  O
	// O0
	//  O
	//
	//  O
	// O0O

	Shape_Rotate (T, CLOCKWISE) ;

	// pivot should not move
	TEST_CHECK (T->blocks[0].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[0].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[1].x == blocks[0].x - 1) ;
	TEST_CHECK (T->blocks[1].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[2].x == blocks[0].x + 1) ;
	TEST_CHECK (T->blocks[2].y == blocks[0].y) ;

	TEST_CHECK (T->blocks[3].x == blocks[0].x) ;
	TEST_CHECK (T->blocks[3].y == blocks[0].y + 1) ;

	Shape_Free (&T) ;
}

TEST_LIST = {
	{"Shape_I_New", test_Shape_I_New},
 	{"Shape_L_New", test_Shape_L_New},
	{"Shape_O_New", test_Shape_O_New},
	{"Shape_S_New", test_Shape_S_New},
	{"Shape_T_New", test_Shape_T_New},
	{"Shape_Shift", test_Shape_Shift},
	{"Shape_Push",  test_Shape_Push},
	{"Shape_I_Rotate", test_Shape_I_Rotate},
	{"Shape_L_Rotate", test_Shape_L_Rotate},
	{"Shape_O_Rotate", test_Shape_O_Rotate},
	{"Shape_S_Rotate", test_Shape_S_Rotate},
	{"Shape_T_Rotate", test_Shape_T_Rotate},
	{NULL, NULL}
} ;

