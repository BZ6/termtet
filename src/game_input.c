#include "io.h"
#include "game_threads.h"

#include "game_input.h"

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
