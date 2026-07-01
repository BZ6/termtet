#ifndef __GAME_THREADS_H__
#define __GAME_THREADS_H__


#include <threads.h>

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

/* Функция для записи сообщения между потоками
 */
void write_message(mtx_t *mtx, ThreadMessage msg);

/* Функция для чтения сообщения между потоками
 */
ThreadMessage read_message(mtx_t *mtx);

#endif // __GAME_THREADS_H__
