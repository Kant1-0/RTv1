/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 00:30:30 by qfremeau          #+#    #+#             */
/*   Updated: 2017/01/04 16:31:07 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	*select_copied_obj(const UCHAR t, void *p_obj)
{
	t_sphere	*sphere;
	void		*o;

	if (t == OBJ_SPHERE)
	{
		sphere = (t_sphere*)p_obj;
		o = (void*)new_sphere(sphere->center, sphere->radius);
	}
	else
		o = NULL;
	return (o);
}

static void	*select_obj(t_vec3 *p, const double f, const UCHAR t)
{
	void	*o;

	if (t == OBJ_SPHERE)
		o = (void*)new_sphere(p, f);
	else if (t == OBJ_PLANE_XY)
		o = (void*)new_plane_xy(1, 2, 1, 1, 1);
	else
		o = NULL;
	return (o);
}

static void	*select_hit(const UCHAR t)
{
	void	*f;

	if (t == OBJ_SPHERE)
		f = (void*)&hit_sphere;
	else if (t == OBJ_PLANE_XY)
		f = (void*)&hit_plane_xy;
	else
		f = NULL;
	return (f);
}

static void	*select_scatter(const UCHAR t)
{
	void	*s;

	if (t == MAT_LAMBERT)
		s = (void*)&scatter_lambertian;
	else if (t == MAT_METAL)
		s = (void*)&scatter_metal;
	else if (t == MAT_DIELECT)
		s = (void*)&scatter_dielectric;
	else if (t == MAT_DIFF_LIGHT)
		s = (void*)&scatter_diffuse_light;
	else
		s = NULL;
	return (s);
}

t_obj		*new_object(void *obj, const UCHAR type_obj, t_mat *mat, \
	const UCHAR type_mat)
{
	t_obj	*o;

	o = malloc(sizeof(t_obj));
	o->type_obj = type_obj;
	o->p_obj = obj;
	o->hit = select_hit(o->type_obj);
	o->p_mat = mat;
	o->p_mat->type_mat = type_mat;
	o->p_mat->scatter = select_scatter(o->type_obj);
	if (type_mat == MAT_DIFF_LIGHT)
		o->p_mat->emitted = o->p_mat->albedo;
	else
		o->p_mat->emitted = v3_new_vec(0.0, 0.0, 0.0);
	return (o);
}

t_obj		*copy_object(t_obj *obj)
{
	t_obj	*o;

	o = malloc(sizeof(t_obj));
	o->type_obj = obj->type_obj;
	o->p_obj = select_obj(v3_new_vec(0.0, 0.0, 0.0), 0.39, o->type_obj);
	o->hit = select_hit(o->type_obj);
	o->p_mat = new_material(obj->p_mat->albedo, obj->p_mat->t);
	o->p_mat->type_mat = obj->p_mat->type_mat;
	o->p_mat->scatter = select_scatter(o->type_obj);
	if (o->p_mat->type_mat == MAT_DIFF_LIGHT)
		o->p_mat->emitted = obj->p_mat->albedo;
	else
		o->p_mat->emitted = v3_new_vec(0.0, 0.0, 0.0);
	return (o);
}
