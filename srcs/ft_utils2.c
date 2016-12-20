/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 16:37:29 by qfremeau          #+#    #+#             */
/*   Updated: 2016/12/20 18:46:50 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_imgparam		*new_imgparam(char* name)
{
	t_imgparam		*p;

	p = (t_imgparam*)malloc(sizeof(t_imgparam));
	p->path = name;
	return (p);
}

void			set_imgparam(t_imgparam *param, char* name)
{
	param->path = name;
}

t_viewparam		*new_viewparam(t_scene *scene)
{
	t_viewparam		*p;
	t_obj			**obj;
	t_skybox		*skybox;
	t_cam			*cam;

	cam = init_camera(v3(-0.6, 0.0, -0.6), v3(0.0, 0.0, 0.0), \
		v3(0.0, -1.0, 0.0), 60.0, 1.0, 0.0, 0.5);
	obj = (t_obj**)malloc(2 * sizeof(t_obj*));
	obj[0] = copy_object(scene->obj[0]);
	obj[1] = new_object(v3_new_vec(0.0, 1.5, 0.0), 0.5, OBJ_SPHERE, \
		v3_new_vec(1.0, 1.0, 1.0), MAT_DIFF_LIGHT, NULL_PARAM);
	skybox = new_skybox(v3_new_vec(0.4, 0.4, 0.4), \
		v3_new_vec(0.9, 0.9, 0.9), SKYBX_GRADIENT);
	p = (t_viewparam*)malloc(sizeof(t_viewparam));
	p->scene = new_scene(cam, obj, skybox);
	p->scene->obj_nb = 2;
	p->obj = scene->obj[0];
	return (p);
}

void			set_viewparam(t_viewparam *p, t_rt *rt, int x, int y)
{
	t_hit		param;
	t_ray		*ray;
	float		u;
	float		v;

	u = (float)x / (float)rt->r_view->w;
	v = (float)y / (float)rt->r_view->h;
	ray = camera_ray(rt->scene->cam, u, v);
	param.pos = v3_new_vec(0.0, 0.0, 0.0);
	param.normal = v3_new_vec(0.0, 0.0, 0.0);
	if (hit_list(rt->scene, ray, 0.001, FLT_MAX, &param))
	{
		free(p->scene->obj[0]);
		p->scene->obj[0] = copy_object(rt->scene->obj[param.i_lst]);
		p->obj = rt->scene->obj[param.i_lst];
	}
	v3_free(param.pos);
	v3_free(param.normal);
	free_ray(ray);
}

//join_free
