/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 18:00:00 by qfremeau          #+#    #+#             */
/*   Updated: 2016/12/22 18:16:12 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
  SDL_WINDOWEVENT_RESIZED needs more work, and other rendering functions 
  need to get dynamic values not just MACROS.
*/

void		button_list(t_rt *rt, t_input *in)
{
	t_button		*button_curs;

	button_curs = rt->panel->lst_button;
	while (button_curs != NULL)
	{
		if (in->m_x > button_curs->rect->x && \
			in->m_x < (button_curs->rect->x + button_curs->rect->w) && \
			in->m_y > button_curs->rect->y && \
			in->m_y < (button_curs->rect->y + button_curs->rect->h))
		{
			button_curs->hover = TRUE;
			if (in->button[SDL_BUTTON_LEFT])
			{
				button_curs->action(button_curs->param);
				SDL_Delay(300);
			}
		}
		else
			button_curs->hover = FALSE;
		button_curs = button_curs->next;
	}
}

void		rt_events(t_rt *rt, t_input *in)
{
	esdl_update_events(in, &rt->esdl->run);
	if (in->quit)
		pthread_join(rt->render_th, NULL);
	button_list(rt, in);
	if (in->window == SDL_WINDOWEVENT_RESIZED)
	{
		pthread_cancel(rt->render_th);
		pthread_join(rt->render_th, NULL);
		rt->render = 0;
		udpate_view(rt);
		free(rt->panel);
		free(rt->r_menu);
		reset_menu(rt);
		display_rt(rt);
		pthread_create(&rt->render_th, NULL, (void*)render_loop, (void*)rt);
		in->window = 0;
	}
	else if (in->button[SDL_BUTTON_LEFT])
	{
		if (in->m_x < rt->r_view->w && in->m_y < rt->r_view->h)
		{
			set_viewparam(rt->panel->viewparam, rt, in->m_x, in->m_y);
			update_menu(rt);
		}
	} // MOVE
	else if (rt->suspend == TRUE && in->key[SDL_SCANCODE_RIGHT] && \
		!in->button[SDL_BUTTON_RIGHT])
	{
		set_camera(rt->scene->cam, v3(rt->scene->cam->look_from->x - 1, \
			rt->scene->cam->look_from->y, rt->scene->cam->look_from->z), \
			v3(rt->scene->cam->look_at->x - 1, rt->scene->cam->look_at->y, \
			rt->scene->cam->look_at->z), *(rt->scene->cam->v_up));
		udpate_view(rt);
		render(rt);
		rt->render = TRUE;
	}
	else if (rt->suspend == TRUE && in->key[SDL_SCANCODE_LEFT] && \
		!in->button[SDL_BUTTON_RIGHT])
	{
		set_camera(rt->scene->cam, v3(rt->scene->cam->look_from->x + 1, \
			rt->scene->cam->look_from->y, rt->scene->cam->look_from->z), \
			v3(rt->scene->cam->look_at->x + 1, rt->scene->cam->look_at->y, \
			rt->scene->cam->look_at->z), *(rt->scene->cam->v_up));
		udpate_view(rt);
		render(rt);
		rt->render = TRUE;
	}
	else if (rt->suspend == TRUE && in->key[SDL_SCANCODE_UP] && \
		!in->button[SDL_BUTTON_RIGHT])
	{
		set_camera(rt->scene->cam, v3(rt->scene->cam->look_from->x, \
			rt->scene->cam->look_from->y + 1, rt->scene->cam->look_from->z), \
			v3(rt->scene->cam->look_at->x, rt->scene->cam->look_at->y + 1, \
			rt->scene->cam->look_at->z), *(rt->scene->cam->v_up));
		udpate_view(rt);
		render(rt);
		rt->render = TRUE;
	}
	else if (rt->suspend == TRUE && in->key[SDL_SCANCODE_DOWN] && \
		!in->button[SDL_BUTTON_RIGHT])
	{
		set_camera(rt->scene->cam, v3(rt->scene->cam->look_from->x, \
			rt->scene->cam->look_from->y - 1, rt->scene->cam->look_from->z), \
			v3(rt->scene->cam->look_at->x, rt->scene->cam->look_at->y - 1, \
			rt->scene->cam->look_at->z), *(rt->scene->cam->v_up));
		udpate_view(rt);
		render(rt);
		rt->render = TRUE;
	} // ROTATE 
	else if (rt->suspend == TRUE && in->key[SDL_SCANCODE_RIGHT] && \
		in->button[SDL_BUTTON_RIGHT])
	{
		set_camera(rt->scene->cam, v3(rt->scene->cam->look_from->x + cos(M_PI/12), \
			rt->scene->cam->look_from->y, rt->scene->cam->look_from->z + sin(M_PI/12)), \
			*(rt->scene->cam->look_at), *(rt->scene->cam->v_up));
		printf("%f %f %f\n", rt->scene->cam->look_from->x, \
			rt->scene->cam->look_from->y, rt->scene->cam->look_from->z);
		udpate_view(rt);
		render(rt);
		rt->render = TRUE;
	}
	else if (rt->suspend == TRUE && in->key[SDL_SCANCODE_LEFT] && \
		in->button[SDL_BUTTON_RIGHT])
	{
		set_camera(rt->scene->cam, v3(rt->scene->cam->look_from->x + 0.5, \
			rt->scene->cam->look_from->y, rt->scene->cam->look_from->z - 0.5), \
			*(rt->scene->cam->look_at), *(rt->scene->cam->v_up));
		udpate_view(rt);
		render(rt);
		rt->render = TRUE;
	}
	else if (rt->suspend == TRUE && in->key[SDL_SCANCODE_UP] && \
		in->button[SDL_BUTTON_RIGHT])
	{
		set_camera(rt->scene->cam, v3(rt->scene->cam->look_from->x, \
			rt->scene->cam->look_from->y + 1, rt->scene->cam->look_from->z), \
			*(rt->scene->cam->look_at), *(rt->scene->cam->v_up));
		udpate_view(rt);
		render(rt);
		rt->render = TRUE;
	}
	else if (rt->suspend == TRUE && in->key[SDL_SCANCODE_DOWN] && \
		in->button[SDL_BUTTON_RIGHT])
	{
		set_camera(rt->scene->cam, v3(rt->scene->cam->look_from->x, \
			rt->scene->cam->look_from->y - 1, rt->scene->cam->look_from->z), \
			*(rt->scene->cam->look_at), *(rt->scene->cam->v_up));
		udpate_view(rt);
		render(rt);
		rt->render = TRUE;
	}

}
