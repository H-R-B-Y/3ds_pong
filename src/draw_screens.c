/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:09:51 by hbreeze           #+#    #+#             */
/*   Updated: 2025/03/24 13:33:27 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pong1.h"

void	draw_top(t_meta *meta)
{
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(meta->top, C2D_Color32(0, 0, 0, 255));  // Clear screen (black)
	C2D_SceneBegin(meta->top);

	// draw paddles
	// bool C2D_DrawRectSolid(float x, float y, float z, float w, float h, u32 clr)
	C2D_DrawRectSolid(
		meta->paddles[0].pos.x,
		meta->paddles[0].pos.y,
		1,
		meta->paddle_width,
		meta->paddle_height,
		C2D_Color32(0xff, 0x0, 0x0, 0xFF)
	);
	
	C2D_DrawRectSolid(
		meta->paddles[1].pos.x,
		meta->paddles[1].pos.y,
		1,
		meta->paddle_width,
		meta->paddle_height,
		C2D_Color32(0x0, 0xFF, 0x0, 0xFF)
	);

	// draw ball
	C2D_DrawCircleSolid(
		meta->ball.pos.x,
		meta->ball.pos.y,
		1,
		meta->ball.size,
		C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF)
	);

	// End rendering
	C3D_FrameEnd(0);
}

void	draw_bottom(t_meta *meta)
{
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(meta->bottom, C2D_Color32(0, 0, 0, 255));  // Clear screen (black)
	C2D_SceneBegin(meta->bottom);

	// Draw a filled square
	// C2D_DrawRectSolid(50, 50, 0, 100, 100, C2D_Color32(255, 0, 0, 255));  // Red square

	// End rendering
	C3D_FrameEnd(0);
}
