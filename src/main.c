/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:30:43 by hbreeze           #+#    #+#             */
/*   Updated: 2025/03/24 13:58:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pong1.h"

void	main_loop(t_meta *meta)
{
	u32		key;
	t_pos	changed;

	while (aptMainLoop())
	{
		hidScanInput();
		consoleClear();
		key = hidKeysDown();
		if (key & KEY_START)
			break;
		changed = do_key_checks(meta, hidKeysDownRepeat());
		do_physics_checks(meta, changed);
		draw_top(meta);
		// draw_bottom(meta);
		// gfxFlushBuffers();
		// gfxSwapBuffers();
		// gspWaitForVBlank();
	}
}

int	main()
{
	t_meta	meta;

	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, 0);
	meta = init_meta();
	main_loop(&meta);
	gfxExit();
	return (0);
}
