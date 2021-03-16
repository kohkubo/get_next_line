#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif
#define SAFE_FREE(p) {free(p);p = NULL;}
#define ERROR -1
#define CONTINUE 1
#define END 0

static size_t ft_strlen(char *s)
{
	size_t i = 0;

	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static char *free_return(char **s, char *p)
{
	SAFE_FREE(*s);
	return (p);
}

static char *ft_strjoin(char *s, char *d)
{
	char *dst;
	char *head;

	if (!(dst = malloc(ft_strlen(s) + ft_strlen(d) + 1)))
		return (NULL);
	head = dst;
	if (s)
		while (*s)
			*dst++ = *s++;
	if (d)
		while (*d)
			*dst++ = *d++;
	*dst = '\0';
	return (head);
}

static char *ft_strn(char *s)
{
	if (!s)
		return (0);
	while (*s && *s != '\n')
		s++;
	return (s);
}

static int is_n(char *s)
{
	if (!s)
		return (0);
	while (*s && *s != '\n')
		s++;
	return (*s == '\n');
}

static int store_line(char **line, char **s)
{
	char *tmp;
	char *dst;

	tmp = *s;
	if (!(dst = malloc(ft_strn(tmp) - tmp + 1)))
	{
		SAFE_FREE(*s);
		return (ERROR);
	}
	*line = dst;
	while (*tmp && *tmp != '\n')
		*dst++ = *tmp++;
	*dst = '\0';
	if (*tmp == '\0')
	{
		SAFE_FREE(*s);
		return (END);
	}
	else
		*s = free_return(s, ft_strjoin(++tmp, NULL));
	return (CONTINUE);
}

static int read_file(int fd, char **s)
{
	char *buf;
	ssize_t rc;

	if (!(buf = malloc((size_t)BUFFER_SIZE + 1)))
		return (ERROR);
	rc = 1;
	while (0 < rc && !is_n(*s))
	{
		if ((rc = read(fd, buf, BUFFER_SIZE)) == ERROR)
		{
			SAFE_FREE(buf);
			SAFE_FREE(*s);
			return (ERROR);
		}
		buf[rc] = '\0';
		if (!(*s = free_return(s, ft_strjoin(*s, buf))))
			return (ERROR);
	}
	SAFE_FREE(buf);
	if (rc == 0)
		return (END);
	return (CONTINUE);
}

int get_next_line(int fd, char **line)
{
	static char *s;

	if (!line || BUFFER_SIZE <= 0 || read(fd, 0, 0) == ERROR)
		return (ERROR);
	if (read_file(fd, &s) == ERROR)
		return (ERROR);
	return (store_line(line, &s));
}
