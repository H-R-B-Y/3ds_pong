/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:19:51 by hbreeze           #+#    #+#             */
/*   Updated: 2025/03/24 14:01:26 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pong1.h"

t_pos	do_key_checks(t_meta *meta, u32 key)
{
	t_pos a;

	printf("KEY_UP: %d\n", !!(key & KEY_UP));
	printf("KEY_DOWN: %d\n", !!(key & KEY_DOWN));
	printf("KEY_X: %d\n", !!(key & KEY_X));
	printf("KEY_B: %d\n", !!(key & KEY_B));
	a = (t_pos){0, 0};
	if (key & KEY_UP && ++a.x)
	{
		
		meta->paddles[0].velocity.y -= 0.1; // paddle 0:  goes up
	}
	if (key & KEY_DOWN && ++a.x)
	{
		
		meta->paddles[0].velocity.y += 0.1; // paddle 0:  goes down
	}
	if (key & KEY_X && ++a.y)
	{
		meta->paddles[1].velocity.y -= 0.1; // paddle 1:  goes up
		
	}
	if (key & KEY_B && ++a.y)
	{
		meta->paddles[1].velocity.y += 0.1; // paddle 1:  goes down
		
	}
	return (a);
}
