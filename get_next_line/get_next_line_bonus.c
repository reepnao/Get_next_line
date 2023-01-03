/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbattal <42kocaeli.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:26:46 by rbattal           #+#    #+#             */
/*   Updated: 2022/12/27 21:23:59 by rbattal          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char *line)
{
	int		i;
	char	*str;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_left_str(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	free(line);
	return (str);
}

char	*ft_read_to_left_str(int fd, char *line)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(line, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		line = ft_strjoin(line, buff);
	}
	free(buff);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*line[4096];

	if (fd < 0 || 0 >= BUFFER_SIZE)
		return (0);
	line[fd] = ft_read_to_left_str(fd, line[fd]);
	if (!line[fd])
		return (NULL);
	str = ft_get_line(line[fd]);
	line[fd] = ft_new_left_str(line[fd]);
	return (str);
}
// #include <stdio.h>
// int main()
// {
// int fd = open("main.txt", O_RDONLY);
// char    *i;
// int fdr = open("main2.txt", O_RDONLY);
// char    *s;
// while ((i = get_next_line(fd)) != NULL)
// {
//     printf("%s", i);
// 	free(i);
// }
// printf("\n");
// while ((s = get_next_line(fdr)) != NULL)
// {
//     printf("%s", s);
// 	free(s);
// }
// }