/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:41:13 by mfahmi            #+#    #+#             */
/*   Updated: 2024/11/22 08:41:16 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_new_line(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*find_new_line(int fd, char *remainder)
{
	ssize_t	size_of_read;
	char	*buffer;
	char	*ptr;

	buffer = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	while (!ft_new_line(buffer, '\n'))
	{
		size_of_read = read(fd, buffer, BUFFER_SIZE);
		if (size_of_read < 0)
			return (free(remainder), free(buffer), NULL);
		else if (size_of_read == 0)
			break ;
		buffer[size_of_read] = '\0';
		if (!remainder)
			remainder = ft_strdup(buffer);
		else
		{
			ptr = remainder;
			remainder = ft_strjoin(ptr, buffer);
			free(ptr);
		}
	}
	free(buffer);
	return (remainder);
}

static int	line_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

static char	*find_line(char **remainder, int length_line)
{
	char	*line;
	int		i;
	char	*ptr;
	char	*new_reminder;

	ptr = *remainder;
	i = 0;
	line = malloc((length_line + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (ptr[i] && i < length_line)
	{
		line[i] = ptr[i];
		i++;
	}
	line[i] = '\0';
	new_reminder = ft_substr(ptr, i);
	free(*remainder);
	*remainder = new_reminder;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	int			length_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = find_new_line(fd, remainder);
	if (!remainder)
		return (NULL);
	length_line = line_len(remainder);
	line = find_line(&remainder, length_line);
	if (!*remainder)
	{
		free(remainder);
		remainder = NULL;
	}
	return (line);
}
// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
//     int fd1;
//     char *line1 = NULL;

//     fd1 = open("roo.txt", O_RDONLY);
//     if (fd1 < 0)
//     {
//         perror("Error opening roo.txt");
//         return (1);
//     }

//     while (1)
//     {
//         line1 = get_next_line(fd1);

//         if (line1 == NULL)
//             break ;
//         if (line1)
//         {
//             printf("File1: %s", line1);
//             free(line1);
//         }
//     }
//     close(fd1);
//     return (0);
// }
