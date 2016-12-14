/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popzelife <popzelife@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 18:46:53 by qfremeau          #+#    #+#             */
/*   Updated: 2016/12/13 21:23:46 by popzelife        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_iter		*lst_new_iter(t_iter **iter, int i)
{
	t_iter		*new;
	t_iter		*curs;

	new = NULL;
	new = (t_iter*)malloc(sizeof(t_iter));
	if (new == NULL)
		return (NULL);
	new->s = i;
	new->next = NULL;
	if (*iter == NULL)
		return (new);
	else
	{
		curs = *iter;
		while (curs->next != NULL)
			curs = curs->next;
		curs->next = new;
	}
	return (*iter);
}

t_thread	*lst_new_thread(t_thread **thread)
{
	t_thread		*new;
	t_thread		*curs;

	new = NULL;
	new = (t_thread*)malloc(sizeof(t_thread));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	if (*thread == NULL)
		return (new);
	else
	{
		curs = *thread;
		while (curs->next != NULL)
			curs = curs->next;
		curs->next = new;
	}
	return (*thread);
}

t_surface	*lst_new_surface(t_surface **surface, t_surfparam param, \
	SDL_Renderer *render, void(f)(SDL_Surface*, const SDL_Rect, const int))
{
	t_surface		*new;
	t_surface		*curs;

	new = NULL;
	new = (t_surface*)malloc(sizeof(t_surface));
	if (new == NULL)
		return (NULL);
	new->rect = esdl_copy_rect(*(param.rect));
	new->surf = esdl_create_surface(new->rect->w, new->rect->h);
	f(new->surf, *(new->rect), param.color);
	new->text = SDL_CreateTextureFromSurface(render, new->surf);
	SDL_FreeSurface(new->surf);
	new->next = NULL;
	if (*surface == NULL)
		return (new);
	else
	{
		curs = *surface;
		while (curs->next != NULL)
			curs = curs->next;
		curs->next = new;
	}
	return (*surface);
}

t_text	*lst_new_string(t_text **text, t_strparam param, \
	SDL_Renderer *render, void(f)(SDL_Surface*, const SDL_Rect, const int))
{
	t_text		*new;
	t_text		*curs;

	new = NULL;
	new = (t_text*)malloc(sizeof(t_text));
	if (new == NULL)
		return (NULL);

	new->text = f(param.string, param.font, param.rx, render);

	new->next = NULL;
	if (*text == NULL)
		return (new);
	else
	{
		curs = *text;
		while (curs->next != NULL)
			curs = curs->next;
		curs->next = new;
	}
	return (*text);
}
