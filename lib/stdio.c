/*
 * stdio.c
 *
 *  Created on: January 2, 2020
 *      Author: lidq
 */

#include <stdio.h>
#include <libc.h>
#include <fcntl.h>
#include <stdarg.h>
#include <mm.h>
#include <sem.h>
#include <buff_s.h>

static char *buff = NULL;
static sem_t sem_p = {0};

int printf(char *fmt, ...)
{
	if (buff == NULL)
	{
		buff = malloc(BUFF_SIZE_UART);
		sem_init(&sem_p, 1);
	}

	if (buff == NULL)
	{
		return -1;
	}

	sem_wait(&sem_p);

	va_list ap;
	int ret;
	va_start(ap, fmt);
	ret = vsnprintf(buff, BUFF_SIZE_UART, fmt, ap);
	va_end(ap);

	write(1, buff, ret);

	sem_post(&sem_p);
	return ret;
}

struct stat
{
};

int _fstat(int fd, struct stat *pStat)
{
	return 0;
}

int _close(int fd)
{
	return -1;
}

int _write(int fd, char *pBuffer, int size)
{
	return -1;
}

int _isatty(int fd)
{
	return 1;
}

int _lseek(int fd, int offset, int size)
{
	return -1;
}

int _read(int fd, char *pBuffer, int size)
{
	return -1;
}

int _sbrk(int increment)
{
	return -1;
}
