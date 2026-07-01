#ifndef __GAME_THREADS_H__
#define __GAME_THREADS_H__


#include <threads.h>

#include "io.h"

typedef enum {
	MSG_PAUSE = 0,
	MSG_UNDEFINED,
	MSG_STOP,
	MSG_ROTATE,
	MSG_LEFT,
	MSG_RIGHT,
	MSG_DOWN
} ThreadMessage;

extern mtx_t mtx;

/* Функция инициализации сообщения
 */
void init_message(void);

/* Функция-поток логики игры
 */
int game_logic(void *arg);

/* Функция-поток обработки ввода
 */
int game_input(void *arg);

#endif // __GAME_THREADS_H__
