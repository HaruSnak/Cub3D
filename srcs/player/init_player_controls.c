/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_controls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:04:30 by tmoeller          #+#    #+#             */
/*   Updated: 2024/12/07 17:08:44 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// from Andy
void	controls(t_game *game)
{
	if (game->ply->w)
		move_forward(game);
	if (game->ply->s)
		move_backwards(game);
	if (game->ply->a)
		move_left(game);
	if (game->ply->d)
		move_right(game);
	if (game->ply->left)
		rotate_left(game);
	if (game->ply->right)
		rotate_right(game);
}

//new
int	ft_update_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	controls(game);
	cast_rays(game);
	return (0);
}

//new
void	init_player(t_game *game)
{
	game->ply->time = get_time();
	game->ply->old_time = game->ply->time;
	game->ply->sensitivity = 0.00001;				// AJOUTEZ CETTE LIGNE
	game->ply->frame_time = 0.0;
	game->ply->move_speed = 0.1; // Set a default value
	game->ply->rotate_speed = 0.05; // Set a default value
	game->ply->plane_x = 0.66;
	game->ply->plane_y = 0.0;
	game->ply->w = false;
	game->ply->a = false;
	game->ply->s = false;
	game->ply->d = false;
	game->ply->left = false;
	game->ply->right = false;
}
