/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:37:33 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/10/16 13:35:13 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// split_next_line(save, buff, line)
// {
// 	// line = NULL;
// 	if '\n' not in buff
// 		save = save + buff;
// 		return ;
// 	line = (save + buff)[:'\n'];
// 	save = (save + buff)['\n':]; // if len(buff['\n':]) == 0, save = NULL
// }

static void	split_next_line(static char **save_p, char **buff_p, char **line_p)
{
	char	*save_plus_buff;
	char	*new_line_pos;

	save_plus_buff = ft_strjoin(*save_p, *buff_p);
	new_line_pos = ft_strchr(save_plus_buff, '\n');
	if (!new_line_pos)
	{
		free(*save_p);
		*save_p = save_plus_buff;
		return ;
	}
	*new_line_pos = '\0';
	*line_p = ft_strdup(save_plus_buff);
	free(*save_p);
	*save_p = ft_strdup(new_line_pos + 1);
	free(save_plus_buff);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*save;
	char		*line;
	ssize_t		code;

	line = NULL;
	split_next_line(&save, NULL, &line);
	if (line)
		return (line);
	buff = malloc((BUFF_SIZE + 1) * sizeof(char));
	while (line == NULL)
	{
		code = read(fd, buff, BUFF_SIZE);
		if (code == 0)
		{
			free(buff);
			return (save);
		}
		else if (code == -1)
		{
			free(buff);
			free(save);
			return (NULL);
		}
		split_next_line(&save, &buff, &line);
	}
	free(buff);
	return (line);
}

//cat "file"と等価
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file", O_RDONLY);
	while ((line = get_next_line(fd)) > 0)
		printf("%s\n", line);
	return (0);
}
