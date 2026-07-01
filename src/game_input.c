#include "io.h"
#include "game_threads.h"

#include "game_input.h"

#define KEY_ESC 27
#define KEY_W 'w'
#define KEY_A 'a'
#define KEY_D 'd'
#define KEY_S 's'
#define KEY_P 'p'

/***
 * Объявления внутренних функций
 ***/

/* Функция обработки вводимого символа
 */
void input_handler(int key);

/***
 * Определения внешних функций
 ***/

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

/* Функция обработки вводимого символа
 */
void input_handler(int key)
{
	switch (key)
	{
		case KEY_ESC:
			// конец игры
			write_message(&mtx, MSG_STOP);
			break;
		case KEY_W:
			// вращение по часовой стрелке
			write_message(&mtx, MSG_ROTATE);
			break;
		case KEY_A:
			// перемещение влево
			write_message(&mtx, MSG_LEFT);
			break;
		case KEY_D:
			// перемещение право
			write_message(&mtx, MSG_RIGHT);
			break;
		case KEY_S:
			// перемещение вниз
			write_message(&mtx, MSG_DOWN);
			break;
		case KEY_P:
			// пауза
			write_message(&mtx, MSG_PAUSE);
			break;
		default:
			// ничего не происходит
			break;
	}
}
