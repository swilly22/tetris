#ifndef __GAME__H_
#define __GAME__H_

#include "board.h"

typedef struct
{
	bool over ;         // game is over
	uint score ;        // game score
	Board board ;       // game board
	uint play_time ;    // how much time palyer been playing
	uint shape_count ;  // number of shapes introduced
} Game ;


// create a new game
Game *Game_New(void) ;

// game main loop
// 
// 1. pick a random shape
// 2. check if game ended
// 3. push shape down the board
void Game_Loop
(
	Game *game
) ;

// free game
void Game_Free
(
	Game **game
) ;

#endif

