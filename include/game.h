#ifndef __GAME_H__
#define __GAME_H__


#include "grid.h"
#include "game_threads.h"

typedef enum {
	GAME_STOP = 0,
	GAME_PAUSE,
	GAME_RUNNING
} GameStatus;

typedef struct {
	Grid grid;
	GameStatus status;
} Game;

/* Функция запуска процесса игры
 */
void run_game(void);

#endif // __GAME_H__
