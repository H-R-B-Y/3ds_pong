/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:45:32 by hbreeze           #+#    #+#             */
/*   Updated: 2025/03/24 23:20:21 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pong1.h"


void	move_paddles(t_meta *meta, t_pos changed)
{
	float friction = 0.95f;  // Friction factor (tweak as needed)
	float epsilon = 0.001f;  // Minimum velocity to consider it stopped

	if (!changed.x)
	{
		meta->paddles[0].velocity.y *= friction;
		if (fabs(meta->paddles[0].velocity.y) < epsilon)
			meta->paddles[0].velocity.y = 0;
	}
	if (!changed.y)
	{
		meta->paddles[1].velocity.y *= friction;
		if (fabs(meta->paddles[1].velocity.y) < epsilon)
			meta->paddles[1].velocity.y = 0;
	}
	meta->paddles[0].pos.y = C2D_Clamp(meta->paddles[0].pos.y
		+ meta->paddles[0].velocity.y,
		0, TOP_SCREEN_HEIGHT - meta->paddle_height);
	meta->paddles[1].pos.y = C2D_Clamp(meta->paddles[1].pos.y
		+ meta->paddles[1].velocity.y,
		0, TOP_SCREEN_HEIGHT - meta->paddle_height);
}

void	check_ball_collide(t_meta *meta)
{ 
	if (meta->ball.pos.x + meta->ball.size >= TOP_SCREEN_WIDTH && meta->ball.velocity.x > 0)
		meta->ball.velocity.x *= -1;
	else if (meta->ball.pos.x - meta->ball.size <= 0 && meta->ball.velocity.x < 0)
		meta->ball.velocity.x *= -1;
	if (meta->ball.pos.y + meta->ball.size >= TOP_SCREEN_HEIGHT && meta->ball.velocity.y > 0)
		meta->ball.velocity.y *= -1;
	else if (meta->ball.pos.y - meta->ball.size <= 0 && meta->ball.velocity.y < 0)
		meta->ball.velocity.y *= -1;
}

void	calc_ball_paddle(t_meta *meta, t_ball *ball, t_paddle *paddle)
{
	float	relative_intersect_y;
	float	bounce_angle;
	float	speed;
	
	relative_intersect_y = (ball->pos.y - paddle->pos.y) / (meta->paddle_height / 2);
	bounce_angle = relative_intersect_y * 45.0f * (M_PI / 180.0f); // Convert to radians
	speed = sqrt(ball->velocity.x * ball->velocity.x + ball->velocity.y * ball->velocity.y);
	ball->velocity.x = speed * cos(bounce_angle);
	ball->velocity.y = speed * sin(bounce_angle);
	if (paddle == &meta->paddles[0])
		ball->velocity.x = fabs(ball->velocity.x); // Ensure it moves right
	else
		ball->velocity.x = -fabs(ball->velocity.x); // Ensure it moves left
}

s16	check_ball_paddle(t_meta *meta, t_ball *ball, t_paddle *paddle)
{
	if (ball->pos.x > paddle->pos.x && ball->pos.x < paddle->pos.x + meta->paddle_width)
		if (ball->pos.y > paddle->pos.y && ball->pos.y < paddle->pos.y + meta->paddle_height)
		return (1);
	return (0);
}

void	do_physics_checks(t_meta *meta, t_pos changed)
{
	move_paddles(meta, changed);
	// check for ball collision
	check_ball_collide(meta);
	if (check_ball_paddle(meta, &meta->ball, &meta->paddles[0]))
		calc_ball_paddle(meta, &meta->ball, &meta->paddles[0]);
	if (check_ball_paddle(meta, &meta->ball, &meta->paddles[1]))
		calc_ball_paddle(meta, &meta->ball, &meta->paddles[1]);
	meta->ball.pos.x += meta->ball.velocity.x;
	meta->ball.pos.y += meta->ball.velocity.y;
}
