#ifndef __SCREEN_H__
#define __SCREEN_H__

// clear entire screen
#define SCREEN_CLEAR() printf ("\033[H\033[J") ;

// set cursor at position x,y
#define SCREEN_GOTO(x,y) printf ("\033[%d;%dH", (y), (x)) ;

#endif

