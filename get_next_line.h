/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:29:13 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/02 12:34:29 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define E_READ -1
# define E_ALLOCATE -2

typedef struct s_gnl
{
	int		fd;
	char	*buf;
	ssize_t	index;
	ssize_t	size;
	char	*line;
	ssize_t	line_size;
	ssize_t	line_index;
}			t_gnl;

char		*ft_realloc(char *buf, ssize_t len);
int			fetch_char(t_gnl *gnl);
int			concat_char(t_gnl *gnl, ssize_t c);
char		*get_next_line(int fd);
int			init_gnl(t_gnl *gnl, int fd);

#endif