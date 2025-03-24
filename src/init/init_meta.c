/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_meta.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:43:26 by hbreeze           #+#    #+#             */
/*   Updated: 2025/03/24 14:28:35 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pong1.h"


t_ball	init_ball(t_pos pos)
{
	return ((t_ball){
		.pos = pos,
		.velocity = init_vec(0.5, 0.5),
		.size = 2
	});
}

t_paddle init_paddle(t_pos pos)
{
	return ((t_paddle){
		.velocity = init_vec(0, 0),
		.pos = pos
	});
}

t_meta	init_meta()
{
	t_meta	meta;

	meta = (t_meta){.top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT),
		.bottom = 0, //  C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT)
		.paddle_width = 10,
		.paddle_height = 30,
		.ball = init_ball(init_pos(0,0)),
		.paddles[0] = init_paddle((t_pos){0,0}),
		.paddles[1] = init_paddle((t_pos){0,0})
	};
	meta.paddles[0].pos = init_pos(meta.paddle_width * 2,
			(TOP_SCREEN_HEIGHT / 2) - (meta.paddle_height / 2));
	meta.paddles[1].pos = init_pos(TOP_SCREEN_WIDTH - (meta.paddle_width * 2),
			(TOP_SCREEN_HEIGHT / 2) - (meta.paddle_height / 2));
	meta.ball.pos = init_pos((TOP_SCREEN_WIDTH / 2) - (meta.ball.size / 2),
		(TOP_SCREEN_HEIGHT / 2) - (meta.ball.size / 2));
	return (meta);
}
