/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoeller <tmoeller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:00:27 by tmoeller          #+#    #+#             */
/*   Updated: 2024/12/16 14:46:32 by tmoeller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	choose_wall_texture(t_game *game)
{
	if (game->ray->side == 0)
	{
		if (game->ray->raydirx > 0)
			game->ray->color = WEST_WALL_TEXTURE;
		else
			game->ray->color = EAST_WALL_TEXTURE;
	}
	else
	{
		if (game->ray->raydiry > 0)
			game->ray->color = NORTH_WALL_TEXTURE;
		else
			game->ray->color = SOUTH_WALL_TEXTURE;
	}
}

// assigns textures based on wall heading as per the subject
// side 0 is a vertical wall (y axis), side 1 horizontal (x axis)
// after, chooses W/E or N/S depending on ray direction

void	draw_vertical_line(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->ray->draw_start)
	{
		my_mlx_pixel_put(&game->img, game->ray->x, y, CEILING_COLOR);
		y++;
	}
	while (y <= game->ray->draw_end)
	{
		my_mlx_pixel_put(&game->img, game->ray->x, y, game->ray->color);
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&game->img, game->ray->x, y, 0x1900FF);
		y++;
	}
}

// draws ceiling, wall and floor in that order of the while loops
// fills all 3 sections of possible texture types of a vertical slice
// my_mlx_pixel_put sets colors of pixels directly in img buffer

void	cast_rays(t_game *game)
{
	int	tex_id; // added for textures

	update_frame_time(game);
	game->ray->x = 0;
	while (game->ray->x < WIN_WIDTH)
	{
		ft_init(game);
		ft_dda_algo(game);
		process_dda(game);
		perp_init(game);
		calculate_line_height(game);
		//choose_wall_texture(game);
		//draw_vertical_line(game);
		tex_id = choose_tex_id(game); // for textures, and below
		draw_textured_line(game, tex_id);
		game->ray->x++;
	}
	mlx_put_image_to_window(game->p_mlx_init, game->p_mlx_window, game->img.i, 0, 0);
}
// the "main" of raycasting engine
// loops across horizontally and applies all the raycasting functions to
// each x axis point and increments
// outputs final image after completing the pass