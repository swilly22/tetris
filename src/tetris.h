#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define BOARD_WIDTH    10  // tetris board width  (number of columns)
#define BOARD_HEIGHT   20  // tetris board height (number of rows)

// assert
#define ASSERT(X)                                                               \
	if (!(X))                                                               \
	{                                                                       \
		printf ("assertion failed: " __FILE__ " line %d\n", __LINE__) ; \
		assert (false) ;                                                \
	}

#define ASSERT_NOT_NULL(X) ASSERT ((X) != NULL)

// return if expression evaluates to NULL
#define RETURN_IF_NULL(exp)                \
	if ((exp) == NULL)                 \
	{                                  \
		return ;                   \
	}

#endif // __TETRIS_H__

