/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 14:05:44 by qfremeau          #+#    #+#             */
/*   Updated: 2016/12/22 15:24:15 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
  Need sufficient malloc on each pthread #pthread_attr_getstack()
  Need also a pthread_mutex handling as rt->tab is shared between threads
*/

void		set_thread(t_thread *t, t_rt *rt, int i, int *s)
{
	int		ret;

	t->arg.rt = rt;
	t->arg.scene = rt->scene;
	t->arg.j = i;
	t->arg.tab = rt->tab;
	t->arg.s = s;
	if ((ret = pthread_attr_init(&t->attr)) != 0)
	{
		ft_dprintf(2, "RT error %d - pthread_attr_init failed\n", ret);
		exit(-1);
	}
	if ((ret = pthread_attr_setstack(&t->attr, &(rt->stack), STACK_SIZE)) != 0)
	{
		//ft_dprintf(2, "RT error %d - pthread_attr_setstack failed\n", ret);
		//exit(-1);
	}
	if ((ret = pthread_create(&t->thread, &t->attr, (void*)thread_render, \
		(void*)&t->arg)) != 0)
	{
		ft_dprintf(2, "RT error %d - pthread_create failed\n", ret);
		exit(-1);
	}
}

void		join_thread(t_thread *t)
{
	int		ret;

	if ((ret = pthread_join(t->thread, NULL)) != 0)
	{
		ft_dprintf(2, "RT error %d - pthread_join failed\n", ret);
		exit(-1);
	}
}

void		destroy_thread_attr(t_thread *t)
{
	int		ret;

	if ((ret = pthread_attr_destroy(&t->attr)) != 0)
	{
		ft_dprintf(2, "RT error %d - pthread_attr_destroy failed\n", ret);
		exit(-1);
	}
}

static void	render2(t_rt *rt, t_thread *th_curs)
{
	int			i;

	/*
	  Join all threads
	*/

	i = 0;
	th_curs = rt->t;
	while (i < rt->m_thread)
	{
		join_thread(th_curs);
		th_curs = th_curs->next;
		++i;
	}

	/*
	  Destroy all threads
	*/

	i = 0;
	th_curs = rt->t;
	while (i < rt->m_thread)
	{
		destroy_thread_attr(th_curs);
		th_curs = th_curs->next;
		++i;
	}
}

void		render(t_rt *rt)
{
	t_thread	*th_curs;
	t_iter		*it_curs;
	int			i;

	/*
	  Set all threads
	*/

	i = 0;
	th_curs = rt->t;
	it_curs = rt->iter;
	while (i < rt->m_thread)
	{
		set_thread(th_curs, rt, i, &(it_curs->s));
		th_curs = th_curs->next;
		it_curs = it_curs->next;
		++i;
	}

	printf("Render thread%50s\r", "");
	render2(rt, th_curs);

	ft_printf("Render pass # %3d/%3d %20s\r", rt->iter->s - 1, ALIASING, "");
}