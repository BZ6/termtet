#include <stdio.h>

#include "game_threads.h"

ThreadMessage message;
mtx_t mtx;

/***
 * Объявления внутренних функций
 ***/

/* Функция для записи сообщения между потоками
 */
void write_message(mtx_t *mtx, ThreadMessage msg);

/* Функция для чтения сообщения между потоками
 */
ThreadMessage read_message(mtx_t *mtx);

/* Функция обработки сообщения между потоками
 */
void message_handler(ThreadMessage msg);

/* Функция обработки вводимого символа
 */
void input_handler(int key);

/***
 * Определения внешних функций
 ***/

/* Функция инициализации сообщения
 */
void init_message(void)
{
	message = MSG_UNDEFINED;
}

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

/* Функция-поток обработки ввода
 */
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

/***
 * Определения внутренних функций
 ***/

/* Функция для записи сообщения между потоками
 */
void write_message(mtx_t *mtx, ThreadMessage msg)
{
	mtx_lock(mtx);
	message = msg;
	mtx_unlock(mtx);
}

/* Функция для чтения сообщения между потоками
 */
ThreadMessage read_message(mtx_t *mtx)
{
	ThreadMessage msg;

	mtx_lock(mtx);
	msg = message;
	message = MSG_UNDEFINED;
	mtx_unlock(mtx);

	return msg;
}

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
