#ifndef __GAME_STRUCT_H__
#define __GAME_STRUCT_H__

#include "grid.h"

typedef enum {
	GAME_STOP = 0,
	GAME_PAUSE,
	GAME_RUNNING
} GameStatus;

typedef struct {
	Grid grid;
	GameStatus status;
} Game;

#endif // __GAME_STRUCT_H__
