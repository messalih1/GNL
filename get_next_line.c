/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:00:52 by messalih          #+#    #+#             */
/*   Updated: 2021/12/07 21:03:23 by messalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next(char *trach)
{
	int		i;
	int		x;
	char	*s;

	i = 0;
	x = 0;
	if (trach[0] == '\0')
		return (free(trach), NULL);
	while (trach[i] != '\n' && trach[i] != '\0')
		i++;
	if (trach[i] == '\n')
		i++;
	s = malloc((ft_strlen(trach) - i) * sizeof(char) + 1);
	if (s == NULL)
		return (NULL);
	while (trach[i] != '\0')
		s[x++] = trach[i++];
	s[x] = '\0';
	free(trach);
	return (s);
}

char	*get_line(char *trach)
{
	int		i;
	char	*str;

	i = 0;
	if (trach[0] == '\0')
		return (NULL);
	while (trach[i] != '\n' && trach[i] != '\0')
		i++;
	if (trach[i] == '\n')
		i++;
	str = malloc(i * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (trach[i] != '\n' && trach[i] != '\0')
	{
		str[i] = trach[i];
		i++;
	}
	if (trach[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*get_buff(int fd, char *trach)
{
	char	*buff;
	int		i;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	i = 1;
	while (!ft_strchr(trach, '\n') && i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[i] = '\0';
		trach = ft_strjoin(trach, buff);
	}
	free(buff);
	return (trach);
}

char	*get_next_line(int fd)
{
	static char	*trach;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	trach = get_buff(fd, trach);
	if (trach == NULL)
		return (NULL);
	line = get_line(trach);
	trach = get_next(trach);
	return (line);
}
