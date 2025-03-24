/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong1.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:39:33 by hbreeze           #+#    #+#             */
/*   Updated: 2025/03/24 13:52:23 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PONG1_H
# define PONG1_H

#include <3ds.h>
#include <citro2d.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOP_SCREEN_WIDTH  400
#define TOP_SCREEN_HEIGHT 240

#define BOTTOM_SCREEN_WIDTH  320
#define BOTTOM_SCREEN_HEIGHT 240

typedef struct s_pos	t_pos;
typedef struct s_vec	t_vec;
typedef struct s_paddle	t_paddle;
typedef struct s_ball	t_ball;
typedef struct s_meta	t_meta;

struct	s_vec
{
	float x;
	float y;
};

struct	s_pos
{
	float	x;
	float	y;
};

struct s_paddle
{
	t_pos	pos;
	t_vec	velocity;
};

struct s_ball
{
	t_pos	pos;
	t_vec	velocity;
	u16		size;
};

struct s_meta 
{
	C3D_RenderTarget	*top;
	C3D_RenderTarget	*bottom;
	u16					paddle_width;
	u16					paddle_height;
	t_paddle			paddles[2];
	t_ball				ball;
};

t_meta	init_meta();

static inline t_vec	init_vec(float x, float y)
{
	return ((t_vec){x, y});
}

static inline t_pos	init_pos(s32 x, s32 y)
{
	return ((t_pos){x, y});
}


void	draw_top(t_meta *meta);
void	draw_bottom(t_meta *meta);

t_pos	do_key_checks(t_meta *meta, u32 key);

void	do_physics_checks(t_meta *meta, t_pos changed);

#endif 