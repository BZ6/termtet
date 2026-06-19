#include "io.h"

#if defined(_WIN32) || defined(_WIN64)
	#include <conio.h>
#elif defined(__unix__) || defined(__APPLE__)
	#include <termios.h>
	#include <unistd.h>
#else
	#include <stdio.h>
#endif


#if defined(_WIN32) || defined(_WIN64) // Проверяем, запущена ли программа на Windows
/* Функция получения нажатой клавиши клавиатуры
 */
int get_key(void)
{
	return _getch();
}

#elif defined(__unix__) || defined(__APPLE__) // Проверяем, запущена ли программа на Linux, macOS или другой Unix-системе
/* Функция получения нажатой клавиши клавиатуры
 */
int get_key(void)
{
	struct termios oldt, newt;
	int ch;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return ch;
}

#else // Запасной вариант, если ОС не распознана
/* Функция получения нажатой клавиши клавиатуры
 */
int get_key(void)
{
	printf("\n[Ошибка: ОС не поддерживается. Нажмите Enter]\n");
	return getchar();
}

#endif

/* Отображение строки в терминале
 */
void display(char *str)
{
	
}
