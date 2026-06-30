#ifndef __GAME_H__
#define __GAME_H__


#include "io.h"
#include "grid.h"

typedef enum {
	GAME_STOP = 0,
	GAME_PAUSE,
	GAME_RUNNING
} GameStatus;

typedef enum {
	MSG_STOP = 0,
	MSG_PAUSE,
	MSG_ROTATE,
	MSG_LEFT,
	MSG_RIGHT,
	MSG_DOWN,
	MSG_UNDEFINED
} ThreadMessage;

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
