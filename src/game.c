#include "game.h"

#define GAME_SIZE 8

/***
 * Объявления внутренних функций
 ***/

/* Функция окончания игры
 */
void end_game(Game *game);

/* Функция запуска игры
 */
Game start_game(void);

/***
 * Определения внешних функций
 ***/

/* Функция запуска процесса игры
 */
void run_game(void)
{
	thrd_t game_input_thread, game_logic_thread;
	init_message();

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

/***
 * Определения внутренних функций
 ***/

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
