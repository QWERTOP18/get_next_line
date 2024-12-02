/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:19:30 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/02 13:09:24 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	init_gnl(t_gnl *gnl, int fd)
{
	if (!gnl->buf)
	{
		gnl->fd = fd;
		gnl->buf = (char *)malloc(BUFFER_SIZE + 1);
		if (!gnl->buf)
			return (E_ALLOCATE);
		gnl->buf[BUFFER_SIZE] = '\0';
	}
	gnl->line_size = BUFFER_SIZE;
	gnl->line = (char *)malloc(gnl->line_size + 1);
	if (!gnl->line)
	{
		free(gnl->buf);
		gnl->buf = NULL;
		return (E_ALLOCATE);
	}
	gnl->line[0] = '\0';
	gnl->line_index = 0;
	return (0);
}

int	fetch_char(t_gnl *gnl)
{
	if (gnl->index >= gnl->size)
	{
		gnl->index = 0;
		gnl->size = read(gnl->fd, gnl->buf, BUFFER_SIZE);
		if (gnl->size < 0)
			return (E_READ);
		gnl->buf[gnl->size] = '\0';
	}
	if (gnl->size == 0)
		return (EOF);
	return (gnl->buf[gnl->index++]);
}

int	concat_char(t_gnl *gnl, ssize_t c)
{
	char	*new_line;

	if (gnl->line_index >= gnl->line_size)
	{
		gnl->line[gnl->line_index] = '\0';
		new_line = ft_realloc(gnl->line, gnl->line_size * 2 + 1);
		if (!new_line)
		{
			gnl->line = NULL;
			return (E_ALLOCATE);
		}
		gnl->line = new_line;
		gnl->line_size *= 2;
	}
	gnl->line[gnl->line_index++] = (char)c;
	return (0);
}

char	*get_next_line(int fd)
{
	int				c;
	static t_gnl	gnl;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (NULL);
	if (init_gnl(&gnl, fd) != 0)
		return (NULL);
	while (1)
	{
		c = fetch_char(&gnl);
		if (c == EOF || c == E_READ || concat_char(&gnl, c))
		{
			free(gnl.line);
			free(gnl.buf);
			gnl.buf = NULL;
			gnl.line = NULL;
			return (NULL);
		}
		if (c == '\n' || c == '\0')
			break ;
	}
	gnl.line[gnl.line_index] = '\0';
	return (gnl.line);
}

// #ifndef TEST
// # include <string.h>
// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;

// 	fd = 0;
// 	if (argc > 1)
// 		fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		if (!line)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
// #endif