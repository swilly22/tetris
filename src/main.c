#include "game.h"
#include "shape.h"
#include <time.h>
#include <stdlib.h>

int main
(
	int argc,
	const char **argv
)
{
	// seed random
	time_t t ;
	srand ((unsigned) time (&t)) ;

	Game *game = Game_New () ;

	Game_Loop (game) ;

	printf ("score: %d\n", game->score) ;

	Game_Free (&game) ;
}	

