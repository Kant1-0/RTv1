/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esdl_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 10:11:48 by qfremeau          #+#    #+#             */
/*   Updated: 2016/12/16 18:07:21 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	esdl_init_esdl(t_esdl *esdl, const int rx, const int ry)
{
	esdl->eng.input = (t_input*)malloc(sizeof(t_input));
	ft_memset(esdl->eng.input, 0, sizeof(t_input));
	esdl->fps.current = 0;
	esdl->fps.fps = 0;
	esdl->fps.update = 0;
	esdl->run = 1;
	esdl->ttf = 0;
	esdl->fps.framelimit = 0;
	esdl->fps.limit = MAX_FPS;
	esdl->eng.rx = rx;
	esdl->eng.ry = ry;
	esdl_fps_limit(esdl);
}

int			esdl_init(t_esdl *esdl, const int rx, const int ry, char * name)
{
	int		ret;

	esdl_init_esdl(esdl, rx, ry);
	ret = 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ret = -1;
		ft_dprintf(2, "SDL_Init() failed: %s\n", SDL_GetError());
	}
	esdl->eng.win = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, rx, ry, \
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	if (!esdl->eng.win)
	{
		ret = -1;
		ft_dprintf(2, "SDL_CreateWindow() failed: %s\n", SDL_GetError());
	}
	esdl->eng.render = SDL_CreateRenderer(esdl->eng.win, -1,
			SDL_RENDERER_ACCELERATED);
	if (!esdl->eng.render)
	{
		ret = -1;
		ft_dprintf(2, "SDL_CreateRenderer() failed: %s\n", SDL_GetError());
	}
	return (ret);
}
