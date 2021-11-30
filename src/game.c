#include "game.h"
#include "tetris.h"
#include "screen.h"
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/select.h>

// key codes
#define SPACE        32
#define LEFT_ARROW   37
#define RIGHT_ARROW  39
#define DOWN_ARROW   40

// number of miliseconds between each timeout
#define INTERVAL_MS  200

Game *Game_New(void) {
	Board board = Board_New () ;
	Game  *game = calloc (sizeof (Game), 1) ;

	ASSERT_NOT_NULL (game) ;

	game->over         =  false  ;
	game->score        =  0      ;
	game->board        =  board  ;
	game->play_time    =  0      ;
	game->shape_count  =  0      ;

	return game ;
}

// game main loop
// 
// 1. pick a random shape
// 2. check if game ended
// 3. push shape down the board
void Game_Loop
(
	Game *game
) {
	SCREEN_CLEAR () ;

	//---------------------------------------------------------------------
	// random shape queue
	//---------------------------------------------------------------------
	Shape *random_shapes[2] ;
	random_shapes[0] = Shape_RandomShape () ;
	random_shapes[1] = Shape_RandomShape () ;

	Board board = game->board ;

	//---------------------------------------------------------------------
	// setup input timeout
	//---------------------------------------------------------------------
	
	fd_set rfds ;        // read-only set of file descriptors
	struct timeval tv ;  // timeout
	int retval ;

	// Wait up to one second
	tv.tv_sec   =  0 ;
	tv.tv_usec  =  1000 * 200 ;

	//---------------------------------------------------------------------
	// game loop
	//---------------------------------------------------------------------

	while (!game->over)
	{
		// pop random shape from queue
		Shape *shape = random_shapes[0] ;
		assert (shape != NULL) ;

		// push a new shape to queue
		random_shapes[0] = random_shapes[1] ;
		random_shapes[1] = Shape_RandomShape () ;

		//....
		if (Board_Intersect (board, shape))
		{
			game->over = true ;
			break ;
		}

		// place shape on board
		Board_SetShape (board, shape) ;
		Board_Print (board) ;

		do
		{
			char key = DOWN_ARROW;

			// wait for player input or timeout
			// watch stdin (fd 0) to see when it has input
			FD_ZERO (&rfds) ;
			FD_SET (STDIN_FILENO, &rfds) ;

			//retval = select (1, &rfds, NULL, NULL, &tv) ;
			retval = select (STDIN_FILENO + 1, &rfds, NULL, NULL, NULL) ;
			printf ("retval: %d\n", retval) ;
			assert (retval != -1) ;
			if (retval)
			{
				printf ("user input\n") ;
				//---------------------------------------------
				// user input
				//---------------------------------------------

				assert (FD_ISSET(0, &rfds) == true) ;
				//printf ("sec: %ld, usec: %d\n", tv.tv_sec, tv.tv_usec) ;
				read (STDIN_FILENO, &key, 1) ;
				printf ("key: %d\n", key) ;
			}
			else
			{
				printf ("timeout\n") ;
				//---------------------------------------------
				// timeout
				//---------------------------------------------
				
				key = DOWN_ARROW ;

				// reset timeout
				//printf ("sec: %ld, usec: %d\n", tv.tv_sec, tv.tv_usec) ;
				tv.tv_sec   =  0 ;
				tv.tv_usec  =  1000 * INTERVAL_MS ;
			}

			// try to move shape
			Board_RemoveShape (board, shape) ;

			switch (key)
			{
				case LEFT_ARROW:
					// try to shift left
					Shape_ShiftLeft (shape) ;
					break;
				case RIGHT_ARROW:
					Shape_ShiftRight (shape) ;
					break;
				case DOWN_ARROW:
					Shape_PushDown (shape) ;
					break;
				case SPACE:
					Shape_Rotate (shape, CLOCKWISE) ;
					break;
				default:
					break;

			}

			bool invalid_move = Board_Intersect (board, shape);
			if (invalid_move)
			{
				//---------------------------------------------
				// undo
				//---------------------------------------------
				switch (key)
				{
					case LEFT_ARROW:
						Shape_ShiftRight (shape) ;
						break;
					case RIGHT_ARROW:
						Shape_ShiftLeft (shape) ;
						break;
					case DOWN_ARROW:
						Shape_PushUp (shape) ;
						break;
					case SPACE:
						Shape_Rotate (shape, COUNTER_CLOCKWISE) ;
						break;
					default:
						break;

				}
			}

			// persist shape to board
			Board_SetShape (board, shape) ;
			Board_Print (board) ;

			// break if shape failed to drop down one row
			if(invalid_move && key == DOWN_ARROW)
			{
				break;
			}
		} while (true) ;

		//-------------------------------------------------------------
		// update board, game score
		//-------------------------------------------------------------

		int rows_cleared = Board_ClearFullRows (board) ;
		if (rows_cleared > 0)
		{
			// TODO: validate scoring
			game->score += pow (2, rows_cleared) ;
		}

		Shape_Free (&shape) ;

	} // end of game loop

	// free shapes in queue
	Shape_Free (&random_shapes[0]) ;
	Shape_Free (&random_shapes[1]) ;
}

void Game_Free
(
	Game **game
) {
	RETURN_IF_NULL (game) ;

	Game *g = *game ;
	Board_Free ( &(g->board)) ;

	free (g) ;
	
	*game = NULL ;
}

