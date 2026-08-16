#include <stdio.h>
#include <time.h> // для sleep

#include "grid.h"
#include "io.h"
#include "game_threads.h"

#include "game_logic.h"

#define GAME_SIZE 8

typedef enum {
	GAME_STOP = 0,
	GAME_PAUSE,
	GAME_RUNNING
} GameStatus;

typedef struct {
	Grid grid;
	GameStatus status;
} Game;

// TODO: сейчас тут не логика игры а логика треда игры, надо сделать к примеру передачу всех коллбеков из модуля game
// нужного для игры или создать еще отдельный файл где будет реальная логика игры.
// Если делать коллбеки то нужна структрура из двух структур:
// 1. Содержит информацию и действия с структурой игры
// 2. Содержит действия по нажаитю клавиш, а если точнее что делать на эти нажатые клавиши (message_handler)
// решено хардкодить пока что, так как хочется чтобы логика игры просто работала, а потом можно будет рефакторить

/***
 * Объявления внутренних функций
 ***/

/* Функция обработки сообщения между потоками
 */
void message_handler(ThreadMessage msg, Game *game);

/* Функция окончания игры
 */
void end_game(Game *game);

/* Функция запуска игры
 */
Game start_game(void);

/* Функция засыпания потока
 */
void sleep(void);

/* Функция двжения блока вниз
 */
//Grid brick_move_down(Grid grid);

/***
 * Определения внешних функций
 ***/

/* Функция-поток логики игры
 */
int game_logic(void *arg)
{
	Game game;
	char *str;
	int msg;

	game = start_game();

	while (game.status != GAME_STOP)
	{

		msg = read_message(&mtx);
		message_handler(msg, &game);

		if (game.status == GAME_PAUSE)
		{
			continue;
		}

		str = str_grid(game.grid);
		display(str);

		sleep();
	}

	end_game(&game);

	printf("thread game_logic end\n");
	return 0;
}

/***
 * Определения внутренних функций
 ***/

/* Функция обработки сообщения между потоками
 */
void message_handler(ThreadMessage msg, Game *game)
{
	switch (msg)
	{
		case MSG_STOP:
			// конец игры
			printf("game over\n");
			game->status = GAME_STOP;
			break;
		case MSG_ROTATE:
			// вращение по часовой стрелке
			printf("rotate clockwise\n");
			break;
		case MSG_LEFT:
			// перемещение влево
			printf("move left\n");
			break;
		case MSG_RIGHT:
			// перемещение право
			printf("move right\n");
			break;
		case MSG_DOWN:
			// перемещение вниз
			printf("move down\n");
			break;
		case MSG_PAUSE:
			// пауза
			printf("pause\n");
			game->status = game->status == GAME_RUNNING ? GAME_PAUSE : GAME_RUNNING;
			break;
		default:
			// ничего не происходит
			//printf("nothing\n");
			break;
	}
}

/* Функция запуска игры
 */
Game start_game(void)
{
	Grid grid = create_grid(GAME_SIZE, GAME_SIZE);

	if (!grid.is_success) return (Game)
		{
			.grid = grid,
			.status = GAME_STOP
		};
	return (Game)
	{
		.grid = grid,
		.status = GAME_RUNNING
	};
}

/* Функция окончания игры
 */
void end_game(Game *game)
{
	delete_grid(&(game->grid));
	game->status = GAME_STOP;
}

/* Функция засыпания потока
 */
void sleep(void)
{
	struct timespec delay = {
		.tv_sec = 0,
		.tv_nsec = 100 * 1000
	};
	thrd_sleep(&delay, NULL);
}

/* Функция двжения блока вниз
 */
//Grid brick_move_down(Grid grid)
//{

//}
