/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoeller <tmoeller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:30:10 by tmoeller          #+#    #+#             */
/*   Updated: 2024/12/16 14:30:48 by tmoeller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	get_wallx(t_game *g)
{
	double	wallx;

	if (g->ray->side == 0)
		wallx = g->ply->pos_y + g->ray->perpwalldist * g->ray->raydiry;
	else
		wallx = g->ply->pos_x + g->ray->perpwalldist * g->ray->raydirx;
	return (wallx - floor(wallx));
}

static int	get_texx(t_game *g, t_tex *t, double wallx)
{
	int	texx;

	texx = (int)(wallx * (double)t->w);
	if (g->ray->side == 0 && g->ray->raydirx < 0)
		texx = t->w - texx - 1;
	if (g->ray->side == 1 && g->ray->raydiry > 0)
		texx = t->w - texx - 1;
	return (texx);
}

static void	draw_line_loop(t_game *g, t_tex *t, int texx, double step)
{
	int		y;
	int		texy;
	double	texpos;
	int		color;

	texpos = (g->ray->draw_start - WIN_HEIGHT / 2 + g->ray->line_height / 2)
		* step;
	y = g->ray->draw_start;
	while (y <= g->ray->draw_end)
	{
		texy = (int)texpos & (t->h - 1);
		texpos += step;
		color = get_tex_color(t, texx, texy);
		my_mlx_pixel_put(&g->img, g->ray->x, y, color);
		y++;
	}
}

void	draw_textured_line(t_game *g, int tex_id)
{
	t_tex	*t;
	double	wallx;
	int		texx;
	double	step;

	t = &g->tex[tex_id];
	wallx = get_wallx(g);
	texx = get_texx(g, t, wallx);
	step = 1.0 * t->h / g->ray->line_height;
	draw_line_loop(g, t, texx, step);
}
