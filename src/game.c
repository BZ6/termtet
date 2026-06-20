#include "game.h"

#define GAME_SIZE 8

Game game;

/* Функция запуска игры
 */
Game start_game(void)
{
	Grid grid = create_grid(GAME_SIZE, GAME_SIZE);

	if (!grid.is_success) return (Game)
		{
			.grid = grid,
			.status = STOP
		};
	return (Game)
	{
		.grid = grid,
		.status = RUNNING
	};
}

/* Функция окончания игры
 */
void end_game(Game *game)
{
	delete_grid(&(game->grid));
	game->status = STOP;
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

int game_logic(void *arg);
int game_input(void *arg);

int game_logic(void *arg)
{

}

int game_input(void *arg)
{
	
}

/* Функция игры
 */
void run_game(void)
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
}
