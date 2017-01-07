/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_view.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 14:03:14 by qfremeau          #+#    #+#             */
/*   Updated: 2017/01/07 21:42:15 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		draw_view(t_rt *rt)
{
	rt->r_view = malloc(sizeof (SDL_Rect));
	SDL_GetWindowSize(rt->win_temp, &rt->r_view->w, &rt->r_view->h);
	rt->r_view->x = 0;
	rt->r_view->y = 0;
	rt->r_view->w -= MENU_RX;
	rt->s_view = esdl_create_surface(rt->r_view->w, rt->r_view->h);
	rt->s_process = esdl_create_surface(rt->r_view->w, rt->r_view->h);
	rt->render = TRUE;
}

void		udpate_view(t_rt *rt)
{
	t_iter		*curs_iter;
	int			i;
	int			j;
	int			x;
	int			y;


	i = 0;
	while (i < rt->r_view->w * MULTISAMP)
	{
		j = 0;
		while (j < rt->r_view->h * MULTISAMP)
		{
			v3_set(rt->tab[i][j], 0.0, 0.0, 0.0);
			++j;
		}
		++i;
	}

	curs_iter = rt->iter;
	x = 0;
	y = 0;
	while (curs_iter != NULL)
	{
		curs_iter->s = 1;
		curs_iter->x = x;
		curs_iter->y = y;
		x += RT_SUBXY;
		if (x > rt->r_view->w)
		{
			x = 0;
			y += RT_SUBXY;
		}
		curs_iter = curs_iter->next;
	}

	/*SDL_GetWindowSize(rt->esdl->eng.win, &rt->r_view->w, &rt->r_view->h);
	rt->r_view->x = 0;
	rt->r_view->y = 0;
	rt->r_view->w -= MENU_RX;
	rt->s_view = esdl_scale_surface(rt->s_view, rt->r_view->w, rt->r_view->h);
	esdl_clear_surface(rt->s_view, NULL_RECT, 0xff000000, NULL);
	rt->t_view = SDL_CreateTextureFromSurface(rt->esdl->eng.render, rt->s_view);*/
}
