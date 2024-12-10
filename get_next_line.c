/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:25:32 by agenisse          #+#    #+#             */
/*   Updated: 2024/12/10 23:03:31 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buff)
{
	char	*temp_buff;
	int		bytes_read;

	temp_buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_buff)
		return (NULL);
	bytes_read = read(fd, temp_buff, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(temp_buff);
		return (NULL);
	}										// LA CA SEGFAULT, TA FONCTION C NUL, ELLE DEPEND DE LA TAILLE DU BUFF ET LIT PAS PLUS
	buff = ft_strjoin(buff, temp_buff);
	free(temp_buff);
	return (buff);
}

char	*get_next(char *stock)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	temp = ft_calloc(ft_strlen(stock) - i + 1, sizeof(char));
	if (!temp)
		return (NULL);
	i++;
	j = 0;
	while (stock[i])
		temp[j++] = stock[i++];
	free(stock);
	return (temp);
}

char	*get_line(char *stock)
{
	char	*line;
	int	i;

	i = 0;
	if (!stock)
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (stock[i] && stock[i] != '\n')
	{
		line[i] = stock[i];
		i++;
	}
	if (stock[i] == '\n')
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stock = ft_read(fd, stock);
	if (!stock)
		return (NULL);
	line = get_line(stock);
	stock = get_next(stock);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
