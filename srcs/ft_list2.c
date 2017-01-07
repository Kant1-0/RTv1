/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 16:38:19 by qfremeau          #+#    #+#             */
/*   Updated: 2016/12/16 16:38:29 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		lst_set_surface(t_surface **surface, t_surfparam param, \
	SDL_Renderer *render, void (f)(SDL_Surface*, const SDL_Rect, const int, \
	void*))
{
	t_surface		*curs;
	int				i;

	curs = *surface;
	i = 0;
	while (i++ < param.i_lst)
		curs = curs->next;
	if (param.rect != NULL)
	{
		free(curs->rect);
		curs->rect = esdl_copy_rect(*(param.rect));
	}
	curs->surf = esdl_create_surface(curs->rect->w, curs->rect->h);
	f(curs->surf, *(curs->rect), param.color, param.param);
	curs->text = SDL_CreateTextureFromSurface(render, curs->surf);
	SDL_FreeSurface(curs->surf);
}

void		lst_set_string(t_string **string, t_strparam param, \
	SDL_Renderer *render, t_text (f)(char*, t_font, int[2], SDL_Renderer*))
{
	t_string		*curs;
	int				i;

	curs = *string;
	i = 0;
	while (i++ < param.i_lst)
		curs = curs->next;
	curs->text = f(param.string, param.font, param.xy, render);
}
