/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoeller <tmoeller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:22:58 by tmoeller          #+#    #+#             */
/*   Updated: 2024/12/16 14:57:53 by tmoeller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	load_each_tex(t_game *g, t_tex *t, char *path)
{
	void	*img;
	int		w;
	int		h;

	img = mlx_xpm_file_to_image(g->p_mlx_init, path, &w, &h);
	if (!img)
	{
		printf("Error: cannot load texture %s\n", path);
		exit(EXIT_FAILURE);
	}
	t->img = img;
	t->w = w;
	t->h = h;
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line_len, &t->endian);
	if (!t->addr)
	{
		printf("Error: cannot get texture addr %s\n", path);
		exit(EXIT_FAILURE);
	}
}

void	ft_init_textures(t_game *game)
{
	load_each_tex(game, &game->tex[0], game->map->directions[0]);
	load_each_tex(game, &game->tex[1], game->map->directions[1]);
	load_each_tex(game, &game->tex[2], game->map->directions[2]);
	load_each_tex(game, &game->tex[3], game->map->directions[3]);
}

int	choose_tex_id(t_game *game)
{
	if (game->ray->side == 0)
	{
		if (game->ray->raydirx > 0)
			return (2); // West
		else
			return (3); // East
	}
	else
	{
		if (game->ray->raydiry > 0)
			return (0); // North
		else
			return (1); // South
	}
}

int	get_tex_color(t_tex *t, int x, int y)
{
	char	*dst;

	dst = t->addr + (y * t->line_len + x * (t->bpp / 8));
	return (*(int *)dst);
}
