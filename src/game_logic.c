#include <stdio.h>

#include "game_threads.h"

#include "game_logic.h"

/***
 * Объявления внутренних функций
 ***/

/* Функция обработки сообщения между потоками
 */
void message_handler(ThreadMessage msg);

/***
 * Определения внешних функций
 ***/

/* Функция-поток логики игры
 */
int game_logic(void *arg)
{
	//Game game;
	int msg;
	int is_running = 1;

	//game = start_game();

	while (is_running)
	{
		msg = read_message(&mtx);
		message_handler(msg);
		if (msg == MSG_STOP) {
			is_running = 0;
		}
	}

	//end_game(&game);

	printf("thread game_logic end\n");
	return 0;
}

/***
 * Определения внутренних функций
 ***/

/* Функция обработки сообщения между потоками
 */
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
