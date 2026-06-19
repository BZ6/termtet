#ifndef __GAME_H__
#define __GAME_H__


#include "io.h"
#include "grid.h"

typedef enum {
	STOP = 0,
	PAUSE,
	RUNNING
} GameStatus;

typedef struct {
	Grid grid;
	GameStatus status;
} Game;

/* Функция запуска игры
 */
Game start_game(void);

/* Функция окончания игры
 */
void end_game(Game *game);

/* Функция обработки вводимого символа
 */
void handler(int key);

/* Функция игры
 */
void run_game(void);

#endif // __GAME_H__
