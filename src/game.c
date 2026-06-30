#include <threads.h>

#include "game.h"

#define GAME_SIZE 8

ThreadMessage message;
mtx_t mtx;

/* Объявление внутренних функций */
int game_logic(void *arg);
int game_input(void *arg);
void write_message(mtx_t *mtx, ThreadMessage message);
ThreadMessage read_message(mtx_t *mtx);


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


/* Функция обработки вводимого символа
 */
void handler(int key)
{
	switch (key)
	{
		case 27:
			// конец игры
			printf("game over\n");
			break;
		case 'w':
			// вращение по часовой стрелке
			printf("rotate clockwise\n");
			break;
		case 'a':
			// перемещение влево
			printf("move left\n");
			break;
		case 'd':
			// перемещение право
			printf("move right\n");
			break;
		case 's':
			// перемещение вниз
			printf("move down\n");
			break;
		case 'p':
			// пауза
			printf("pause\n");
			break;
		default:
			// ничего не происходит
			printf("nothing\n");
			break;
	}
}

/* Функция игры
 */
void run_game(void)
{
	thrd_t game_input_thread, game_logic_thread;
	ThreadMessage message = MSG_UNDEFINED;

	if (thrd_create(&game_input_thread, game_input, NULL) != thrd_success)
	{
		printf("Failed to create thread game_input_thread.\n");
		return;
	}
	if (thrd_create(&game_logic_thread, game_logic, NULL) != thrd_success)
	{
		printf("Failed to create thread game_logic_thread.\n");
		return;
	}

	thrd_join(game_input_thread, NULL);
	thrd_join(game_logic_thread, NULL);
}

/* Определения внутренних функций */

int game_logic(void *arg)
{
	Game game;

	game = start_game();

	end_game(&game);

	printf("thread game_logic end\n");
	return 0;
}

int game_input(void *arg)
{
	int is_running = 1;
	int key;

	while (is_running)
	{
		key = get_key();
		handler(key);
		if (key == 27) {
			is_running = 0;
		}
	}

	printf("thread game_input end\n");
	return 0;
}

void write_message(mtx_t *mtx, ThreadMessage msg)
{
	mtx_lock(mtx);
	message = msg;
	mtx_unlock(mtx);
}

ThreadMessage read_message(mtx_t *mtx)
{
	ThreadMessage msg;

	mtx_lock(mtx);
	msg = message;
	mtx_unlock(mtx);

	return msg;
}
