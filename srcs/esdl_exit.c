/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esdl_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popzelife <popzelife@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 11:29:11 by qfremeau          #+#    #+#             */
/*   Updated: 2016/12/12 22:35:19 by popzelife        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				esdl_exit(t_esdl *esdl)
{
	SDL_DestroyRenderer(esdl->eng.render);
	SDL_DestroyWindow(esdl->eng.win);
	if (esdl->ttf)
		TTF_Quit();
	SDL_Quit();
}
