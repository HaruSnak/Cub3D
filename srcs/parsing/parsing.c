/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:58:35 by shmoreno          #+#    #+#             */
/*   Updated: 2024/08/11 17:29:03 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_init_map(t_map *map, bool out_direction, int *i)
{
	if (out_direction && map->directions[0] != NULL
		&& map->directions[1] != NULL && map->directions[2] != NULL
		&& map->directions[3] != NULL && map->directions[4] != NULL
		&& map->directions[5] != NULL)
	{
		map->map[++(*i)] = ft_substr(map->line, 0, ft_strlen(map->line) - 1);
		printf("%d\n", ft_strlen(map->map[*i]));
		printf("map[%d]: %s\n", *i, map->map[*i]);
	}
}

void	ft_init_parsing(t_map *map, char *argv)
{
	bool	out_direction;
	int		count[7];
	int		fd;
	int		i;

	i = -1;
	out_direction = false;
	while (++i < 7)
		count[i] = 0;
	i = -1;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		(printf("Error: Invalid file\n"), exit(EXIT_FAILURE));
	map->line = get_next_line(fd);
	while (map->line != NULL)
	{
		ft_init_dir(map, map->line, count, &out_direction);
		ft_init_map(map, out_direction, &i);
		free(map->line);
		map->line = get_next_line(fd);
	}
	close(fd);
	ft_error_dir(map);
	if (!out_direction)
		(printf("Error: No map\n"), exit(EXIT_FAILURE));
	ft_map_route(map, count[6]);
	exit(EXIT_SUCCESS);
}

int	ft_parse_base(t_map *map, int argc, char **argv)
{
	if (argc != 2)
		return (printf("Error: Invalid number of arguments\n"), EXIT_FAILURE);
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
		return (printf("Error: Invalid file extension\n"), EXIT_FAILURE);
	ft_init_main(map, argv[1]);
	ft_init_parsing(map, argv[1]);
	return (0);
}
