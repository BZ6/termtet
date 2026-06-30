#include <threads.h>

#include "game.h"

#define GAME_SIZE 8

ThreadMessage message;
mtx_t mtx;

/* Объявление внутренних функций */
int game_logic(void *arg);
int game_input(void *arg);
void write_message(mtx_t *mtx, ThreadMessage msg);
ThreadMessage read_message(mtx_t *mtx);
void message_handler(ThreadMessage msg);


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
void input_handler(int key)
{
	switch (key)
	{
		case 27:
			// конец игры
			write_message(&mtx, MSG_STOP);
			break;
		case 'w':
			// вращение по часовой стрелке
			write_message(&mtx, MSG_ROTATE);
			break;
		case 'a':
			// перемещение влево
			write_message(&mtx, MSG_LEFT);
			break;
		case 'd':
			// перемещение право
			write_message(&mtx, MSG_RIGHT);
			break;
		case 's':
			// перемещение вниз
			write_message(&mtx, MSG_DOWN);
			break;
		case 'p':
			// пауза
			write_message(&mtx, MSG_PAUSE);
			break;
		default:
			// ничего не происходит
			break;
	}
}

/* Функция игры
 */
void run_game(void)
{
	thrd_t game_input_thread, game_logic_thread;
	message = MSG_UNDEFINED;

	if (mtx_init(&mtx, mtx_plain) != thrd_success) {
		printf("Failed to init mutex.\n");
		return;
	}

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

	mtx_destroy(&mtx);
}

/* Определения внутренних функций */

int game_logic(void *arg)
{
	Game game;
	int msg;
	int is_running = 1;

	game = start_game();

	while (is_running)
	{
		msg = read_message(&mtx);
		message_handler(msg);
		if (msg == MSG_STOP) {
			is_running = 0;
		}
	}

	end_game(&game);

	printf("thread game_logic end\n");
	return 0;
}

int game_input(void *arg)
{
	int key;
	int is_running = 1;

	while (is_running)
	{
		key = get_key();
		input_handler(key);
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
	message = MSG_UNDEFINED;
	mtx_unlock(mtx);

	return msg;
}

void message_handler(ThreadMessage msg)
{
	switch (msg)
	{
		case MSG_STOP:
			// конец игры
			printf("game over\n");
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
			break;
		default:
			// ничего не происходит
			//printf("nothing\n");
			break;
	}
}
