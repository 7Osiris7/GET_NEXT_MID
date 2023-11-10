/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:09:49 by jruhlman          #+#    #+#             */
/*   Updated: 2023/11/10 12:10:17 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	find_rl(char *buffer)
{
	size_t	i;

	if (!buffer)
		return (-1);
	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buffer[i] == '\0' || buffer[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

static char	*extracte_line(char *line, char *statix, int *r_l, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	reed;
	size_t	lize;

	while (*r_l == -1)
	{
		ft_bzero(buffer, (BUFFER_SIZE + 1));
		reed = read(fd, buffer, BUFFER_SIZE);
		if (reed == -1)
		{
			free(line);
			ft_bzero(statix, (BUFFER_SIZE + 1));
			return (NULL);
		}
		lize = find_rl(buffer);
		ft_strlgcpy(statix, &buffer[lize], (BUFFER_SIZE + 1));
		buffer[lize] = '\0';
		line = ft_strlgjoin(line, buffer, r_l);
		if (reed == 0)
		{
			ft_bzero(statix, (BUFFER_SIZE + 1));
			break ;
		}
	}
	return (line);
}
static char	*locline(char *statix, int *r_l)
{
	char	*line;
	size_t	i;

	if (!statix)
		return (NULL);
	i = 0;
	while (statix[i] && statix[i] != '\n')
		i++;
	i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, statix, i);
	line[i] = '\0';
	if (i > 0 && line[i - 1] == '\n')
		*r_l = i - 1;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	statix[BUFFER_SIZE + 1];
	char	*line;
	int	r_l;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	r_l = -1;
	line = locline(statix, &r_l);
	ft_strlgcpy(statix, &statix[r_l + 1], (BUFFER_SIZE + 1));
	line = extracte_line(line, statix, &r_l, fd);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
